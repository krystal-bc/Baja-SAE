#include <SparkFunDS1307RTC.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#define RTC_SQW 2
#define SD_CS 53

File myFile;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(RTC_SQW, INPUT_PULLUP);
  pinMode(SD_CS, OUTPUT);

  rtc.begin();
  rtc.writeSQW(SQW_SQUARE_1);

  if (SD.begin(SD_CS)) {
    Serial.println("SD card is ready to use.");
    String filename = makeFileName();
    Serial.println(filename);
    myFile = SD.open(filename, FILE_WRITE);
    if (myFile) {
      Serial.print("Writing to " + filename);
      myFile.print("testing");
      myFile.close();
      Serial.println("...done.");
      Serial.print("Opening " + filename);
      myFile = SD.open(filename);
      if (myFile) {
        Serial.println("...done.");
        // read from the file until there's nothing else in it:
        while (myFile.available()) {
          Serial.write(myFile.read());
        }
        // close the file:
        myFile.close();
      } else {
        Serial.println("Error opening " + filename);
      }
    } else {
      Serial.println("SD card failed.");
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}

String makeFileName() {
  rtc.autoTime();
  rtc.update();

  String name = "";

  if (rtc.month() < 10) {
    name += "0" + String(rtc.month());
  } else {
    name += String(rtc.month());
  }
  if (rtc.date() < 10) {
    name += "0" + String(rtc.date());
  } else {
    name += String(rtc.date());
  }
  if (rtc.hour() < 10) {
    name += "0" + String(rtc.hour());
  } else {
    name += String(rtc.hour());
  }
  if (rtc.minute() < 10) {
    name += "0" + String(rtc.minute());
  } else {
    name += String(rtc.minute());
  }
  name += ".txt";
  return name;
} 
