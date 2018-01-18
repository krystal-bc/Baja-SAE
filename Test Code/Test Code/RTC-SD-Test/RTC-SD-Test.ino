/* Krystal Bernal    
   CSULA Baja SAE   
   Last updated: 10/13/17   
    
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
#define BUTTON_PIN 8    
    
RTC_Millis rtc;   
DateTime now;   
File myFile;    
String filename;    
    
int buttonPushCounter = 0;   // counter for the number of button presses    
int buttonState = 0;         // current state of the button   
int lastButtonState = 0;     // previous state of the button    
    
void setup() {    
  Serial.begin(9600);   
  pinMode(BUTTON_PIN, INPUT_PULLUP);    
  pinMode(SD_CS, OUTPUT);   
  rtc.begin(DateTime(F(__DATE__) , F(__TIME__)));   
}   
    
void loop() {   
  now = rtc.now();    
  if (buttonIsPushed()){    
    manageFile();//fix this   
  }   
      
}   
    
void manageFile() {   
  int attempts = 0;   
  if (buttonPushCounter % 2 == 1) {//odd pushes begin writing to a new/existing file    
    Serial.print("SD card initializing...");    
    if (SD.begin(SD_CS)) {//if the SD card initializes properly make a file   
      Serial.print("SD card is ready to use. Making new file: ");   
      filename = makeFileName();    
      Serial.println(filename);   
      myFile = SD.open(filename, FILE_WRITE);   
      if (myFile) {//if the file was made properly    
        Serial.println("...done.");   
        Serial.print("Writing to " + filename);   
        myFile.print("testing");    
      } else {    
        Serial.print("...could not create file.");    
      }   
    } else {//if the SD card doesn't initialize properly    
      Serial.println("initialization failed.");   
    }   
  } else if (buttonPushCounter != 0) { //even pushes: close (save) the file, then reopen it to read its contents    
    if (myFile) {   
      myFile.close();   
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
  buttonState = digitalRead(BUTTON_PIN);    
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
