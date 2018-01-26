/* Krystal Bernal
   CSULA Baja SAE
   Last updated: 1/25/18

   This program uses a button, MicroSD card breakout board, and a RTC to create and write to a timestamped .txt file

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


#include <RTClib.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
#define Serial SerialUSB
#endif

#define SD_CS 53
#define button1 A6
#define LED1 11
#define LED2 10

RTC_Millis rtc;
DateTime now;
File myFile;
String filename;

unsigned int btnState1;
unsigned int lastBtnState1;
unsigned int btnCounter1 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(button1, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  pinMode(SD_CS, OUTPUT);
  rtc.begin(DateTime(F(__DATE__) , F(__TIME__)));
  Serial.print("SD card initializing...");
  if (SD.begin(SD_CS)) {
    Serial.println("SD card is ready to use.");
    digitalWrite(LED1, HIGH);
  } else {
    Serial.println("initialization failed.");
  }
}

void loop() {
  now = rtc.now();
  if (buttonIsPushed()) {
    manageFile();
  }

}

void manageFile() {
  if (btnCounter1 % 2 == 1) {//odd pushes begin writing to a new/existing file
    Serial.print("Making new file: ");
    filename = makeFileName();
    Serial.print(filename);
    myFile = SD.open(filename, FILE_WRITE);
    if (myFile) {//if the file was made properly
      digitalWrite(LED2, HIGH);
      Serial.print("\t...done.");
      Serial.print("Writing to " + filename);
      myFile.print("testing");
    } else {
      Serial.print("...could not create file.");
    }
  } else if (btnCounter1 % 2 == 0 && btnCounter1 > 0) { //even pushes: close (save) the file, then reopen it to read its contents
    if (myFile) {
      myFile.close();
      digitalWrite(LED2, LOW);
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
      Serial.print("button 1 pressed: ");
      Serial.println(btnCounter1);
      //reset button counter
    }
    delay(50);
  }
  lastBtnState1 = btnState1;
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
