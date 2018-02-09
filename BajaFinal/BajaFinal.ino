/* Krystal Bernal
   CSULA Baja SAE
   Last updated: 2/8/18
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
   
   LCD uses A0, D4-10  *A0 not in use
   Wheatstone Bridge uses A0,A1

   LED1 (11)
   LED2 (10)*
   LED3 (30)
   LED4 (36)
   LED5 (12)
*/

//TODO: designate HE/Servos to speed and ratio, update the write statements to SD card, fix range for temperature sensor

#include <WheatstoneBridge.h>
#include <LiquidCrystal.h>
#include <RTClib.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Servo.h>

#define SD_CS 53
#define buttonRecord A6
//#define buttonPIN2 A7
#define tempSensorPIN A14
#define voltSensorPIN A11
#define LEDsdRecording 10
#define LEDsdDetect 11
#define LEDlowBattery 30
//#define LED5 12
//#define LED4

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

Servo rpmServo1;
Servo rpmServo2;

int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button
bool recording;

unsigned int rpm1 = 0;               // RPM value
unsigned int rpm2 = 0;
unsigned long oldTime1 = 0;          // time value
unsigned long oldTime2 = 0;
unsigned long intTime1 = 60000000;   // time intervals
unsigned long intTime2 = 60000000;
int noAction = 0;

float servPos1;             // servo positions
float servPos2;

void setup() {
  lcd.begin(16, 2);
  pinMode(fanPin, OUTPUT);
  analogWrite(fanPin, LOW);
  pinMode(LEDlowBattery, OUTPUT);
  pinMode(LEDsdInitialized, OUTPUT);
  pinMode(LEDsdRecording, OUTPUT);
  pinMode(tempSensorPIN, INPUT);
  pinMode(voltSensorPIN, INPUT);
  digitalWrite(LEDsdInitialized, LOW);
  digitalWrite(LEDsdRecording, LOW);
  digitalWrite(LEDlowBattery, LOW);
  attachInterrupt(5, magnet1, RISING);    // pin 18 = interrupt 5
  attachInterrupt(4, magnet2, RISING);    // pin 19 = interrupt 4
  rpmServo1.attach(servo1PIN);
  rpmServo2.attach(servo2PIN);
  rpmServo1.write(0);
  rpmServo2.write(0);
  pinMode(buttonRecord, INPUT_PULLUP);
  pinMode(SD_CS, OUTPUT);
  rtc.begin(DateTime(F(__DATE__) , F(__TIME__)));
  if (SD.begin(SD_CS)) {
    digitalWrite(LEDsdInitialized, HIGH);
  }
}

void loop() {
  now = rtc.now();
  if (buttonIsPushed()) {
    manageFile();
  }
  readForces();
  readHallEffects();
  printTime(); 
  if (recording) {
    myFile.println("");
  }
  checkVoltage();
  monitorTemp();
}

void manageFile() {
  if (buttonPushCounter % 2 == 1) {//odd pushes begin writing to a new/existing file
    filename = makeFileName();
    myFile = SD.open(filename, FILE_WRITE);
    if (myFile) {//if the file was made properly
      digitalWrite(LEDsdRecording, HIGH);
      myFile.println("Force1,Type,HE1,HE2,RPM1,RPM2,MPH,Ratio,Time"); //make sure heading matches values
      recording = true;
    } else {
      digitalWrite(LEDsdRecording, LOW);
      recording = false;
    }
  } else if (btnCounter1 % 2 == 0 && btnCounter1 > 0) { //even pushes: close (save) the file
    if (myFile) {
      myFile.close();
      digitalWrite(LEDsdRecording, LOW);
      recording = false;
    } else {
      blinkLED(LEDsdRecording);
      recording = false;
    }
  }
}

bool buttonIsPushed() {
  bool wasPushed = false;
  int btn1 = analogRead(button1);
  if (btn1 < 1000) {
    btnState1 = 1;//off
  } else {
    btnState1 = 0;//on
  }
  if (btnState1 != lastBtnState1) {
    if (btnState1 == 0) {
      btnCounter1++;
      wasPushed = true;
      //reset button counter
    }
    delay(50);
  }
  lastBtnState1 = btnState1;
  //reset button counter
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

void readForces() {

  int force1 = cell_1.measureForce() * 0.49;
  int force2 = cell_2.measureForce() * 0.49;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Load1:");
  lcd.setCursor(10, 0);
  lcd.print("Load2:");
  lcd.setCursor(0, 1);
  String forceType1 = "";
  lcd.print(abs(force1), DEC);
  lcd.setCursor(4, 1);
  if (force1 > 0) {
    forceType1 = "T";
  } else {
    forceType1 = "C";
  }
  lcd.print(forceType1);
  if (recording) {
    myFile.print(abs(force1), DEC);
    myFile.print(",");
    myFile.print(forceType1);
    myFile.print(",");
  }
  lcd.setCursor(10, 1);
  lcd.print("NoConn");           // delete when reading load 2
  /*
    String forceType2 = "";
    lcd.print(abs(force2), DEC);
    lcd.setCursor(4, 1);
    if (force2 > 0) {
    forceType2 = "T";
    } else {
    forceType2 = "C";
    }
    lcd.print(forceType2);
    if (recording) {
    myFile.print(abs(force1), DEC);
    myFile.print(",");
    myFile.print(forceType2);
    myFile.print(",");
    }
  */
  delay(50);
}

void readHallEffects() {
  rpm1 = 60000000 / intTime1;   // rev/min = (60s/1min)*(60000ms/60s)*(1rev/timeIn(ms))
  rpm2 = 60000000 / intTime2;

  if (noAction > 10) {                    // if 10 loops pass with no magnetic detection
    rpm1 = 0;                             // reset servo positions to 0
    rpm2 = 0;
    noAction = 11;                        // prevent overflow of int
  }

  float mph = rpm2*0.43211;
  servPos1 = map(rpm2, 0, mph, 180, 0);
  rpmServo1.write(servPos1);
  float ratio = rpm1/rpm2;
  if (ratio > 4){
    ratio = 4;
  }
  servPos2 = map(rpm2, 0, ratio, 180, 0);
  rpmServo2.write(servPos2);
  
  if (recording) {
    myFile.print(rpm1);
    myFile.print(",");
    myFile.print(rpm2);
    myFile.print(",");
    myFile.print(mph);
    myFile.print(",");
    myFile.print(ratio);
    myFile.print(",");
  }

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
  //include when adding new data fields currentTime += ",";
  myFile.print(currentTime);
}

void checkVoltage() {
  float batteryLimit = 9.5;
  int voltageRaw = analogRead(voltSensorPIN);
  //values of the onboard resistors
  float R1 = 30000.0;
  float R2 = 7500.0;
  //5:1 converstion ratio
  float vOut = (voltageRaw * 5.0) / 1024.0;
  float vIn = vOut / (R2 / (R1 + R2));

  if (vIn < batteryLimit) {
    digitalWrite(LEDlowBattery, HIGH);
  } else {
    digitalWrite(LEDlowBattery, LOW);
  }
}

void monitorTemp() {
  float temperatureRaw = analogRead(tempSensorPIN);
  //converts raw data into degrees fahrenheit
  float tempF = ((5.0 * temperatureRaw * 100.0)/1024.0);
  //keep threshold?
  if (tempF > 80){
   digitalWrite(fanPin, HIGH); 
  } else{
    digitalWrite(fanPin, LOW);
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
