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

//TODO: integrate HE sensors/servos and update the write statements to SD card

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
#define LEDsdRecording 11
#define LEDsdDetect 10
//#define LED5 12
#define LEDlowBattery 1
//#define LED4 0

#define servo1PIN 44
#define servo2PIN 46
#define fanPWMpin 13

RTC_Millis rtc;
DateTime now;

File myFile;
String filename;

WheatstoneBridge cell_1(A0, 365, 675, 0, 1000);
WheatstoneBridge cell_2(A1, 365, 675, 0, 1000);

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

Servo speedServo1;
Servo ratioServo2;

int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

int force1;
int force2;

void setup() {
  pinMode(buttonRecord, INPUT_PULLUP);
  pinMode(SD_CS, OUTPUT);
  rtc.begin(DateTime(F(__DATE__) , F(__TIME__)));
  lcd.begin(16, 2);
  speedServo1.attach(servo1PIN);
  ratioServo2.attach(servo2PIN);
  speedServo1.write(0);
  ratioServo2.write(0);
  pinMode(fanPWMpin, OUTPUT);
  analogWrite(fanPWMpin, 0);
  pinMode(LEDlowBattery, OUTPUT);
  pinMode(LEDsdDetect, OUTPUT);
  pinMode(LEDsdRecording, OUTPUT);
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
  printForces();
  printForces();
  //runHE();  //is this staying in loop or getting its own method?
  printTime();
  myFile.println("");
  checkVoltage();
}

void manageFile() {
  if (buttonPushCounter % 2 == 1) {//odd pushes begin writing to a new/existing file
    if (SD.begin(SD_CS)) {//if the SD card initializes properly make a file
      digitalWrite(LEDsdDetect, HIGH);
      filename = makeFileName();
      myFile = SD.open(filename, FILE_WRITE);
      if (myFile) {//if the file was made properly
        digitalWrite(LEDsdRecording, HIGH);
        myFile.println("Force1, Type, HE1, HE2, Ratio, Speed, Time"); //make sure heading matches values
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
  buttonState = digitalRead(buttonRecord);
  if (buttonState != lastButtonState) {
    if (buttonState == LOW) {
      // if the current state is LOW then the button went from unpushed to pushed:
      buttonPushCounter++;
      wasPushed = true;
    } else {
      // if the current state is LOW then the button went from on to off:
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
  
  myFile.print(abs(force1));
  lcd.print(abs(force1), DEC);
  lcd.setCursor(4, 1);
  if (force1 > 0) {
    lcd.print("T");
    myFile.print(", T,");
  } else {
    lcd.print("C");
    myFile.print(", C,");
  }

  lcd.setCursor(10, 1);
  lcd.print("NoConn");           // delete when reading load 2
  /*
  lcd.print(abs(force2),DEC);
  lcd.setCursor(15,1);
  myFile.print(abs(force2));
  if (force2 > 0) {
    lcd.print("T");
    myFile.print(", T,");
  } else {
    lcd.print("C");
    myFile.print(", C,");
  }
  */
  delay(50);
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

  if (vIn < batteryLimit) {
    digitalWrite(LEDlowBattery, HIGH);
  } else {
    digitalWrite(LEDlowBattery, LOW);
  }
}

float readTemp() {
  float temperature = analogRead(tempSensorPIN);
  //converts raw data into degrees celsius and prints it out: 500mV/1024
  temperature = map(x,0,1024,-55.0,150.0);
  //converts celsius into fahrenheit
  temperature = (temperature * 9 / 5) + 32;
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
