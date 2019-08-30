#include <SPI.h>
#include <SD.h>

#define SD_CS 10
#define HE_Pin1 A3
//#define HE_Pin2 A4

File myFile;

unsigned long currentTime1 = 0;
unsigned long oldTime1 = 0;

bool detect1 = false;
bool oldDetect1 = false;

//unsigned long currentTime2 = 0;
//unsigned long oldTime2 = 0;

//bool detect2 = false;
//bool oldDetect2 = false;

void setup() {
  Serial.begin(2000000);
  pinMode(HE_Pin1, INPUT);
  //pinMode(HE_Pin2, INPUT);
  pinMode(SD_CS, OUTPUT);

  if (SD.begin(SD_CS)) {
    myFile = SD.open("HEDATA.txt", FILE_WRITE);
    if (myFile) {
      myFile.println("HE1, micros, HE2, micros");
    }
    myFile.close();
  }
}

void loop() {
  int HE_Raw1 = analogRead(HE_Pin1);
  //int HE_Raw2 = analogRead(HE_Pin2);

  if (HE_Raw1 < 325) {
    detect1 = true;
  } else {
    detect1 = false;
  }
  if ((detect1 != oldDetect1) && detect1) {
    currentTime1 = micros();
    float rpm1 = (60 * 1000000) / (currentTime1 - oldTime1);
    Serial.println(rpm1);
    myFile = SD.open("HEDATA.txt", FILE_WRITE);
    myFile.print("RPM 1: ");
    myFile.print(rpm1);
    myFile.print(", micros: ");
    myFile.println(micros());
    myFile.close();
    oldTime1 = currentTime1;
  }

  oldDetect1 = detect1;
}
