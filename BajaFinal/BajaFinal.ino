/* Krystal Bernal
   CSULA Baja SAE
   Last updated: 11/10/17

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

//TODO: integrate HE sensors, LEDs, voltage sensor, temperature sensor, fan
//update the write statements to SD card

#include <WheatstoneBridge.h>
#include <LiquidCrystal.h>
#include <RTClib.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Servo.h>

#define SD_CS 53
#define buttonPIN 8
#define tempSensorPIN A1
#define voltSensorPIN A2
#define LEDlowBattery 13
#define LEDsdDetect 12
#define LEDsdRecording 11
//#define LED4 10
//#define LED5 9
//#define LED6 8
#define servo1PIN 44
#define servo2PIN 45
#define fanPWMpin 3

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

int force1;
int force2;

void setup() {
  pinMode(buttonPIN, INPUT_PULLUP);
  pinMode(SD_CS, OUTPUT);
  rtc.begin(DateTime(F(__DATE__) , F(__TIME__)));
  lcd.begin(16, 2);
  rpmServo1.attach(servo1PIN);
  rpmServo2.attach(servo2PIN);
  rpmServo1.write(0);
  rpmServo2.write(0);
  analogWrite(fanPWMpin, 0);
  pinMode(LEDlowBattery, OUTPUT);
  pinMode(LEDsdDetect, OUTPUT);
  pinMode(LEDsdRecording, OUTPUT);
  pinMode(fanPWMpin, OUTPUT);
  pinMode(tempSensorPIN, INPUT);
  pinMode(voltSensorPIN, INPUT);
  digitalWrite(LEDsdDetect, LOW);
  digitalWrite(LEDsdRecording, LOW);
  digitalWrite(LEDlowBattery, LOW);
}

void loop() {
  now = rtc.now();
  if (buttonIsPushed()) {
    manageFile();
  }
  printForces();//TODO: write to SD card
  checkVoltage();
  writeFan(readTemp());
}

void manageFile() {
  if (buttonPushCounter % 2 == 1) {//odd pushes begin writing to a new/existing file
    if (SD.begin(SD_CS)) {//if the SD card initializes properly make a file
      digitalWrite(LEDsdDetect, HIGH);
      filename = makeFileName();
      myFile = SD.open(filename, FILE_WRITE);
      if (myFile) {//if the file was made properly
        digitalWrite(LEDsdRecording, HIGH);
        myFile.print("testing");
      } else {
        digitalWrite(LEDsdRecording, LOW);
      }
    } else {//if the SD card doesn't initialize properly
      digitalWrite(LEDsdDetect, LOW);
    }
  } else if (buttonPushCounter != 0) { //even pushes: close (save) the file, then reopen it to read its contents
    if (myFile) {
      myFile.close();
      digitalWrite(LEDsdRecording, LOW);
    } else {
      blinkLED(LEDsdRecording);
    }
  }
}

bool buttonIsPushed() {
  bool wasPushed = false;
  buttonState = digitalRead(buttonPIN);
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
  String name = "";

  if (now.month() < 10) {
    name += "0" + String(now.month());
  } else {
    name += String(now.month());
  }

  if (now.day() < 10) {
    name += "0" + String(now.day());
  } else {
    name += String(now.day());
  }

  if (now.hour() < 10) {
    name += "0" + String(now.hour());
  } else {
    name += String(now.hour());
  }

  if (now.minute() < 10) {
    name += "0" + String(now.minute());
  } else {
    name += String(now.minute());
  }
  name += ".txt";
  return name;
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
  if (force1 > 0) {
    lcd.print(abs(force1), DEC);
    lcd.setCursor(4, 1);
    lcd.print("T");
    Serial.print(abs(force1));
    Serial.print(" T\t");
  } else {
    lcd.print(abs(force1), DEC);
    lcd.setCursor(4, 1);
    lcd.print("C");
    Serial.print(abs(force1));
    Serial.print(" C\t");
  }

  lcd.setCursor(10, 1);           // tab indent
  Serial.print("Load2: ");

  if (force2 > 0) {
    lcd.print("NoConn");           // delete when reading load 2
    Serial.print("NoConn");
    //lcd.print(abs(force2),DEC);
    //lcd.setCursor(15,1);
    //lcd.print("T");
    //Serial.print(abs(force2));
    //Serial.print(" T\t");
  } else {
    lcd.print("NoConn");           // delete when reading load 2
    Serial.print("NoConn");
    //lcd.print(abs(force2),DEC);
    //lcd.setCursor(15,1);
    //lcd.print("C");
    //Serial.print(abs(force2));
    //Serial.print(" C\t");
  }
  Serial.println();
  delay(50);
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

float readTemp() {
  float temperature = analogRead(tempSensorPIN);
  //converts raw data into degrees celsius and prints it out: 500mV/1024
  //temperature = map(x,0,1024,-55.0,150.0); //this might work better
  temperature = temperature * (500 / 1024);
  Serial.print("CELSIUS: ");
  Serial.print(temperature);
  Serial.println("*C ");
  //converts celsius into fahrenheit
  temperature = (temperature * 9 / 5) + 32;
  Serial.print("FAHRENHEIT: ");
  Serial.print(temperature);
  Serial.println("*F");
  return temperature;
}

void writeFan(float temperature) {
  int fanSpeed = map(temperature, 80, 302, 0, 255); //change this to proper range
  analogWrite(fanPWMpin, fanSpeed);
}

void blinkLED(int LEDpin) {
  for (int i = 0; i <= 10; i++) {
    digitalWrite(LEDpin, HIGH);
    delay(1000);
    digitalWrite(LEDpin, LOW);
    delay(1000);
  }
}
