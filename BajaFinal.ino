#include <WheatstoneBridge.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <SPI.h>
#include <SD.h>

#define btnRIGHT  1
#define btnUP     2
#define btnDOWN   4
#define btnLEFT   8
#define btnSELECT 16
#define btnNONE   32

WheatstoneBridge wsb_strain1(A0, 365, 675, 0, 1000);
WheatstoneBridge wsb_strain2(A1, 365, 675, 0, 1000);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// SD Card Variables
File myFile;
int pinCS = 53;

byte read_LCD_buttons()
{
  // read the value from the sensor
  int adc_key_in = analogRead(A5);

  if (adc_key_in > 1000) return btnNONE;
  if (adc_key_in < 50)   return btnRIGHT;
  if (adc_key_in < 250)  return btnUP;
  if (adc_key_in < 450)  return btnDOWN;
  if (adc_key_in < 650)  return btnLEFT;
  if (adc_key_in < 850)  return btnSELECT;

  return btnNONE;                // when all others fail, return this.
}

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

int analogPin;
byte button;

Servo rpmServo1;          // initialize servos
Servo rpmServo2;

void setup()
{
  Serial.begin(115200);
  pinMode(pinCS, OUTPUT);                 // Chip Select pin for SD Card
  lcd.begin(16, 2);                      // Initialize LCD
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
  
  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  }
  else
  {
    Serial.println("SD card failed.");
    return;
  }
}
int val1;
int valRaw1;
int val2;
int valRaw2;


void loop()
{
  if (timeDiv > timeDivMax)
  {
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
    }
    else
    {
      lcd.print(abs(val1), DEC);
      lcd.setCursor(4, 1);
      lcd.print("C");
    }

    lcd.setCursor(10, 1);           // tab indent

    if (val2 > 0)
    {
      lcd.print("NoConn");           // delete when reading load 2
      //lcd.print(abs(val2),DEC);
      //lcd.setCursor(15,1);
      //lcd.print("T");
    }
    else
    {
      lcd.print("NoConn");           // delete when reading load 2
      //lcd.print(abs(val2),DEC);
      //lcd.setCursor(15,1);
      //lcd.print("C");
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

  analogPin = analogRead(A5);

  char buffer[50];                                                                      // create buffer to hold display char's
  i = sprintf(buffer, "RPM1: %d          RPM2: %d   analogRead: %d", rpm1, rpm2, analogPin);        // create display phrase
  for (int j = 0; j <= i; j++)                                                          // cycle through each char
    Serial.print(buffer[j]);                                                            // print each char
  Serial.println();                                                                     // print new line

  servPos1 = map(rpm1, 100, 1800, 160, 0);    // Servo1 range: 0 - 170
  servPos2 = map(rpm2, 100, 1800, 180, 20);   // Servo2 range: 20 - 180
  rpmServo1.write(servPos1);                  // set Servo1 to adjusted position
  rpmServo2.write(servPos2);                  // set Servo2 to adjusted position


  // Write to MicroSD card...
  if (read_LCD_buttons() != btnNONE)
  {
    button = read_LCD_buttons();
  }
  if (button == btnUP)
  {
    lcd.setCursor(7, 1);
    lcd.print("R");
    myFile = SD.open("bajaData.txt", FILE_WRITE);
    if (myFile)
    {
      myFile.print(rpm1);
      myFile.print(",");
      myFile.println(rpm2);
      myFile.close();
    }
    else
    {
      Serial.println("Error opening bajaData.txt");
    }
  }
  else
  {
    // Stop recording data to SD
    lcd.setCursor(7, 1);
    lcd.print(" ");
  }

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

