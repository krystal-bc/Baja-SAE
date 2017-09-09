/* Written by Jovanny Santana and Krystal Bernal
 * for CSULA Baja SAE 2017-2018 
 * Last Updated: 9/8/17
 * 
 * This program reads force in lbs from Load Cells and RPM from Hall Effect Sensors. 
 * Tension and Compression are written to an LCD and RPMs to servos.
 * Select data is written to a MicroSD card.
 * 500kg Load Cell - http://www.robotshop.com/en/500kg-s-type-load-cell.html
 * Wheatstone bridge - http://www.robotshop.com/en/strain-gauge-load-cell-amplifier-shield-2ch.html
 * Hall Effect Sensor - https://www.sparkfun.com/products/9312
 * MicroSD Card Shield - https://www.adafruit.com/product/254
 * Real Time Clock - https://www.sparkfun.com/products/12708
 * LCD Shield - http://www.robotshop.com/en/16x2-lcd-shield-kit-arduino.html
 */

#include <WheatstoneBridge.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <SPI.h>
#include <SD.h>

WheatstoneBridge wsb_strain1(A0, 365, 675, 0, 1000);
WheatstoneBridge wsb_strain2(A1, 365, 675, 0, 1000);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

unsigned int rpm1;        // RPM value
unsigned int rpm2;
unsigned long oldTime1;   // time value
unsigned long oldTime2;
unsigned long intTime1;   // time intervals
unsigned long intTime2;
int servPos1;             // servo positions
int servPos2;
int i;                    // counter for serial monitor display
int noAction;             // counter for loops with nothing happening
int timeDiv;              // counter for divider to slow down refresh rate of display
int timeDivMax;           // divider to slow down refresh rate of display

Servo rpmServo1;          // initialize servos
Servo rpmServo2;

//SD card pins: CLK:52, DO:50, DI:51, CS:53, CD:49?

File myFile;
const int pinCS = 53;    // SD card CS pin
// TO DO: int pinCD = (49?);     //use with 10k resistor to detect if an SD card is present

void setup()
{
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Serial monitor connected.");
  lcd.begin(16, 2);
  attachInterrupt(5, magnet1, RISING);    // pin 18 = sensor1 input
  attachInterrupt(4, magnet2, RISING);    // pin 19 = sensor2 input
  rpmServo1.attach(44);                   // pin 44 = servo1 output
  rpmServo2.attach(45);                   // pin 45 = servo2 output
  rpm1 = 0;                               // initialize rpm1 to 0
  rpm2 = 0;                               // initialize rpm2 to 0
  oldTime1 = 0;                           // start temp timer1
  oldTime2 = 0;                           // start temp timer2
  intTime1 = 60000000;                    // initialize time1 interval
  intTime2 = 60000000;                    // initialize time2 interval
  noAction = 0;
  timeDiv = 0;
  timeDivMax = 2;

  Serial.print("Initializing SD card...");
  if (!SD.begin(pinCS)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SD loaded");
  delay(3000);
  myFile = SD.open("bajaData.txt");

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to bajaData.txt...");
     /*TO DO: program LCD button to indicate the end of a run so that
      * the file can be closed. If the file is not closed, 
      * nothing will actually be saved to the SD card.
    // close the file:
    //myFile.close();*/
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening bajaData.txt");
    lcd.setCursor(0, 0);
    lcd.print("SD error");
    delay(3000);
  }
}

int val1;
int valRaw1;
int val2;
int valRaw2;

void loop()
{
  if (timeDiv > timeDivMax){
    timeDiv = 0;
    
    val1 = wsb_strain1.measureForce() * 0.49;
    valRaw1 = wsb_strain1.getLastForceRawADC();
    val2 = wsb_strain2.measureForce() * 0.49;
    valRaw2 = wsb_strain2.getLastForceRawADC();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Load1:");
    lcd.setCursor(10, 0);
    lcd.print("Load2:");
    lcd.setCursor(0, 1);

    if (val1 > 0)
    {
      lcd.print(abs(val1), DEC);
      lcd.setCursor(4, 1);
      lcd.print("T");
      //myFile.print("T\t");
      //myFile.print(abs(val1));
    }
    else
    {
      lcd.print(abs(val1), DEC);
      lcd.setCursor(4, 1);
      lcd.print("C");
      //myFile.print("C\t");
      //myFile.print(abs(val1));
    }

    lcd.setCursor(10, 1);           // tab indent

    if (val2 > 0)
    {
      lcd.print("NoConn");           // delete when reading load 2
      //lcd.print(abs(val2),DEC);
      //lcd.setCursor(15,1);
      //lcd.print("T");
      //myFile.print("T\t");
      //myFile.print(abs(val2));
    }
    else
    {
      lcd.print("NoConn");           // delete when reading load 2
      //lcd.print(abs(val2),DEC);
      //lcd.setCursor(15,1);
      //lcd.print("C");
      //myFile.print("C\t");
      //myFile.print(abs(val2));
    }
  }
  timeDiv++;
  
  noAction++;
  rpm1 = 60000000 / intTime1;                // rev/min = (60s/1min)*(60000ms/60s)*(1rev/timeIn(ms))
  rpm2 = 60000000 / intTime2;

  if (noAction > 10)                      // if 10 loops pass with no magnetic detection
  {
    rpm1 = 0;                             // reset servo positions to 0
    rpm2 = 0;
    noAction = 11;                        // prevent overflow of int
  }

  char buffer[50];                                                                      // create buffer to hold display char's
  i = sprintf(buffer, "RPM1: %d          RPM2: %d   clicks: %d", rpm1, rpm2, noAction); // create display phrase
  for (int j = 0; j <= i; j++)                                                          // cycle through each char
    Serial.print(buffer[j]);                                                            // print each char
  Serial.println();                                                                     // print new line
  //TO DO: consolidate if the SD card printing can also be formatted with sprintf
  //myFile.print("\tRPM1: );
  //myFile.print(rpm1);
  //myFile.print("\tRPM2: ");
  //myFile.print(rpm2);
  //myFile.print("\tclicks: ");
  //myFile.print(noAction);

  servPos1 = map(rpm1, 100, 1800, 160, 0);    // Servo 1 range: 0 - 170
  servPos2 = map(rpm2, 100, 1800, 180, 20);   // Servo 2 range: 20 - 180
  rpmServo1.write(servPos1);                  // set Servo1 to adjusted position
  rpmServo2.write(servPos2);                  // set Servo2 to adjusted position
  delay(50);
}

void magnet1()                                // when magnet is detected
{
  intTime1 = micros() - oldTime1;             // update time interval
  oldTime1 = micros();                        // update starting point for timer1
  noAction = 0;                               // reset counter
}
void magnet2()                                // when magnet is detected
{
  intTime2 = (micros() - oldTime2);           // update time interval
  oldTime2 = micros();                        // update starting point for timer2
  noAction = 0;                               // reset counter
}


