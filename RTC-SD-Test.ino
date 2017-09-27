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
  rtc.autoTime();

  String filename = String(rtc.month()) + "-" + String(rtc.date()) + "-" + String(rtc.year()) + ".txt";
  Serial.println(filename);
  myFile = SD.open(filename, FILE_WRITE);
  if (SD.begin()) {
    Serial.println("SD card is ready to use.");
    if (myFile) {
      myFile.print("testing");
      myFile.close();
      Serial.write(myFile.read());
    } else {
      Serial.println("Error opening " + filename);
    }
  } else {
    Serial.println("SD card failed.");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
