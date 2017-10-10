#include <RTClib.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
#define Serial SerialUSB
#endif

#define SD_CS 53

RTC_Millis rtc;
DateTime now;
File myFile;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(SD_CS, OUTPUT);
  rtc.begin(DateTime(F(__DATE__) , F(__TIME__)));
  

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
    now = rtc.now();
}

String makeFileName() {
  now = rtc.now();
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
