/* Krystal Bernal
   CSULA Baja SAE
   Last updated: 12/12/17

   -uses a button, MicroSD card breakout board, and a RTC to create and write to a timestamped .txt file
   that can be parsed as a .csv in excel
   -reads forces in lbs from load cells
   -2 hall effect sensors to calculate RPM for drive and driven, displays them on 180 degree servos
   -controls a fan using a temperature sensor
   -LED indicators

   SD Card Wiring
   CLK to pin 52
   DO to pin 50
   DI to pin 51
   CS to pin 53

   RTC Wiring
   SDA to Arduino SDA (communication pin 20)
   SCL to Arduino SCL (communication pin 21)
   omit SQW

*/

//TODO: integrate HE sensors/servos and update the write statements to SD card

#include <WheatstoneBridge.h>
#include <LiquidCrystal.h>
#include <RTClib.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Servo.h>

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
#define Serial SerialUSB
#endif

#define SD_CS 53
#define buttonRecord A6
//#define buttonPIN2 A7
#define tempSensorPIN A14
#define voltSensorPIN A11
#define LEDsdRecording 11
#define LEDsdDetect 10
//#define LED5 12
#define LEDlowBattery 1
//#define LED4 0

#define servo1PIN 44
#define servo2PIN 46
#define fanPin 13

RTC_Millis rtc;
DateTime now;

File myFile;
String filename;

WheatstoneBridge cell_1(A0, 365, 675, 0, 1000);
WheatstoneBridge cell_2(A1, 365, 675, 0, 1000);

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

int force1;
int force2;

Servo rpmServo1;          // initialize servos
Servo rpmServo2;

int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button
bool recording;

int force1;
int force2;

unsigned int rpm1 = 0;        // RPM value
unsigned int rpm2 = 0;

unsigned long oldTime1 = 0;   // time value
unsigned long oldTime2 = 0;
unsigned long intTime1 = 60000000;   // time intervals
unsigned long intTime2 = 60000000;
int noAction = 0;

int servPos1;             // servo positions
int servPos2;

void setup() {
  Serial.begin(112500);
  pinMode(buttonRecord, INPUT_PULLUP);
  pinMode(SD_CS, OUTPUT);
  rtc.begin(DateTime(F(__DATE__) , F(__TIME__)));
  lcd.begin(16, 2);
  pinMode(fanPin, OUTPUT);
  analogWrite(fanPin, LOW);
  pinMode(LEDlowBattery, OUTPUT);
  pinMode(LEDsdDetect, OUTPUT);
  pinMode(LEDsdRecording, OUTPUT);
  pinMode(tempSensorPIN, INPUT);
  pinMode(voltSensorPIN, INPUT);
  digitalWrite(LEDsdDetect, LOW);
  digitalWrite(LEDsdRecording, LOW);
  digitalWrite(LEDlowBattery, LOW);
  attachInterrupt(5, magnet1, RISING);    // pin 18 = interrupt 5
  attachInterrupt(4, magnet2, RISING);    // pin 19 = interrupt 4
  rpmServo1.attach(servo1PIN);
  rpmServo2.attach(servo2PIN);
  rpmServo1.write(0);
  rpmServo2.write(0);

}

void loop() {
  now = rtc.now();
  if (buttonIsPushed()) {
    manageFile();
  }
  printForces();
  readHallEffects();
  printTime();
  myFile.println("");
  checkVoltage();
  monitorTemp();
}

void manageFile() {
  if (buttonPushCounter % 2 == 1) {//odd pushes begin writing to a new/existing file
    Serial.print("SD card initializing...");
    if (SD.begin(SD_CS)) {//if the SD card initializes properly make a file
      digitalWrite(LEDsdDetect, HIGH);
      Serial.print("SD card is ready to use. Making new file: ");
      filename = makeFileName();
      Serial.println(filename);
      myFile = SD.open(filename, FILE_WRITE);
      if (myFile) {//if the file was made properly
        digitalWrite(LEDsdRecording, HIGH);
        Serial.println("...done.");
        Serial.print("Writing to " + filename);
        myFile.println("Force1,Type,HE1,HE2,RPM1,RPM2,Time"); //make sure heading matches values
      } else {
        Serial.print("...could not create file.");
        digitalWrite(LEDsdRecording, LOW);
      }
    } else {//if the SD card doesn't initialize properly
      Serial.println("initialization failed.");
      digitalWrite(LEDsdDetect, LOW);
    }
  } else if (buttonPushCounter != 0) { //even pushes: close (save) the file, then reopen it to read its contents
    if (myFile) {
      myFile.close();
      digitalWrite(LEDsdRecording, LOW);
      Serial.println("...done.");
      Serial.print("Opening " + filename);
      myFile = SD.open(filename);
      Serial.println("...done.");
      while (myFile.available()) {// read from the file until there's nothing else in it
        Serial.write(myFile.read());
      }
      myFile.close();
    } else {
      Serial.println("Error closing " + filename);
      blinkLED(LEDsdRecording);
    }
  }
}

bool buttonIsPushed() {
  bool wasPushed = false;
  buttonState = digitalRead(buttonRecord);
  if (buttonState != lastButtonState) {
    if (buttonState == LOW) {
      // if the current state is LOW then the button went from unpushed to pushed:
      buttonPushCounter++;
      wasPushed = true;
      Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);
    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state
  lastButtonState = buttonState;
  return wasPushed;
}

String makeFileName() {
  String file = "";

  if (now.month() < 10) {
    file += "0" + String(now.month());
  } else {
    file += String(now.month());
  }

  if (now.day() < 10) {
    file += "0" + String(now.day());
  } else {
    file += String(now.day());
  }

  if (now.hour() < 10) {
    file += "0" + String(now.hour());
  } else {
    file += String(now.hour());
  }

  if (now.minute() < 10) {
    file += "0" + String(now.minute());
  } else {
    file += String(now.minute());
  }
  file += ".txt";
  return file;
}

void printForces() {

  force1 = cell_1.measureForce() * 0.49;
  force2 = cell_2.measureForce() * 0.49;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Load1:");
  lcd.setCursor(10, 0);
  lcd.print("Load2:");
  lcd.setCursor(0, 1);

  Serial.print("Load1: ");
  Serial.print(abs(force1));
  myFile.print(abs(force1));
  lcd.print(abs(force1), DEC);
  lcd.setCursor(4, 1);
  if (force1 > 0) {
    Serial.print(" T\t");
    myFile.print(", T,");
    lcd.print("T");
  } else {
    lcd.print("C");
    Serial.print(" C\t");
    myFile.print(", C,");
  }

  lcd.setCursor(10, 1);           // tab indent
  Serial.print("Load2: ");
  lcd.print("NoConn");           // delete when reading load 2
  Serial.print("NoConn");
  /*
  lcd.print(abs(force2),DEC);
  lcd.setCursor(15,1);
  Serial.print(abs(force2));
  myFile.print(abs(force2));
  if (force2 > 0) {
    lcd.print("T");
    Serial.print(" T\t");
    myFile.print(", T,");
  } else {
    lcd.print("C");
    Serial.print(" C\t");
    myFile.print(", C,");
  }
  */
  delay(50);
}

void readHallEffects(){
  rpm1 = 60000000 / intTime1;   // rev/min = (60s/1min)*(60000ms/60s)*(1rev/timeIn(ms))
  rpm2 = 60000000 / intTime2;
  Serial.print("\tRPM 1: ");
  Serial.print(rpm1);
  Serial.print("\tRPM 2: ");
  Serial.println(rpm2);
  if (recording) {
    myFile.print(rpm1);
    myFile.print(",");
    myFile.print(rpm2);
    myFile.print(",");
  }

  if (noAction > 10) {                    // if 10 loops pass with no magnetic detection
    rpm1 = 0;                             // reset servo positions to 0
    rpm2 = 0;
    noAction = 11;                        // prevent overflow of int
  }

  servPos1 = map(rpm1, 100, 1800, 160, 0);    // Servo1 range: 0 - 170
  servPos2 = map(rpm2, 100, 1800, 180, 20);   // Servo2 range: 20 - 180
  rpmServo1.write(servPos1);                  // set Servo1 to adjusted position
  rpmServo2.write(servPos2);                  // set Servo2 to adjusted position

  noAction++;
}

void magnet1() {                              // when magnet is detected
  intTime1 = micros() - oldTime1;             // update time interval
  oldTime1 = micros();                        // update starting point for timer1
  noAction = 0;                               // reset counter
}

void magnet2() {                              // when magnet is detected
  intTime2 = (micros() - oldTime2);           // update time interval
  oldTime2 = micros();                        // update starting point for timer2
  noAction = 0;                               // reset counter
}

void printTime() {
  String currentTime = "";
  if (now.hour() < 10) {
    currentTime += "0" + String(now.hour());
  } else {
    currentTime += String(now.hour());
  }
  currentTime += ":";
  if (now.minute() < 10) {
    currentTime += "0" + String(now.minute());
  } else {
    currentTime += String(now.minute());
  }
  currentTime += ",";
  myFile.print(currentTime);

}

void checkVoltage() {
  float batteryLimit = 10;
  int voltageRaw = analogRead(voltSensorPIN);
  //values of the onboard resistors
  float R1 = 30000.0;
  float R2 = 7500.0;
  //5:1 converstion ratio
  float vOut = (voltageRaw * 5.0) / 1024.0;
  float vIn = vOut / (R2 / (R1 + R2));

  Serial.print("Voltage: ");
  Serial.println(vIn, 2);

  if (vIn < batteryLimit) {
    digitalWrite(LEDlowBattery, HIGH);
  } else {
    digitalWrite(LEDlowBattery, LOW);
  }
}

void monitorTemp() {
  float temperatureRaw = analogRead(tempSensorPIN);
  Serial.print("RAW: ");
  Serial.print(temperatureRaw);
  //converts raw data into degrees celsius
  float tempC = map(temperatureRaw,0,1024,-50,300);//find out range
  Serial.print("\tCELSIUS: ");
  Serial.print(tempC);
  Serial.print("*C \t"); 
  //converts celsius into fahrenheit
  float tempF = (tempC * 9 / 5) + 32;
  Serial.print("FAHRENHEIT: ");
  Serial.print(tempF);
  Serial.println("*F");

  if (tempF > 80){
   digitalWrite(fanPin, HIGH); 
  }
}

void blinkLED(int LEDpin) {
  for (int i = 0; i <= 10; i++) {
    digitalWrite(LEDpin, HIGH);
    delay(1000);
    digitalWrite(LEDpin, LOW);
    delay(1000);
  }
}
