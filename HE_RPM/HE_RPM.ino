/*
   Krystal Bernal
   CSULA Baja SAE
   Last Updated: 8/16/18

   This code uses hall effect sensors and revolving magnets as tachometers for
   reading rpm of drive and driven on a CVT. Ratio is used for tuning.

   Previous code used built-in Arduino interrupt, but was unreliable. According to Arduino's
   documentation: "millis() relies on interrupts to count, so it will never increment inside an ISR.
   micros() works initially, but will start behaving erratically after 1-2 ms."
*/

#include <SPI.h>
#include <SD.h>

#define SD_CS 10
#define HE_Pin1 A3
#define HE_Pin2 A4

File myFile;

unsigned long currentTime1 = 0;
unsigned long oldTime1 = 0;

bool detect1 = false;
bool oldDetect1 = false;

unsigned long currentTime2 = 0;
unsigned long oldTime2 = 0;

bool detect2 = false;
bool oldDetect2 = false;

unsigned short primaryRPM[50];
unsigned long primaryMicros[50];
byte counter1 = 0;

unsigned short secondaryRPM[50];
unsigned long secondaryMicros[50];
byte counter2 = 0;

void setup() {
  pinMode(HE_Pin1, INPUT);
  pinMode(HE_Pin2, INPUT);
  pinMode(SD_CS, OUTPUT);

  if (SD.begin(SD_CS)) {
    //digitalWrite(LED, LOW);
    myFile = SD.open("HEDATA.txt", FILE_WRITE);
    if (myFile) {
      myFile.println("micros, inches");
    }
  }
  zeroPrimary();
  zeroSecondary();
}

void loop() {

  short HE_Raw1 = analogRead(HE_Pin1);
  short HE_Raw2 = analogRead(HE_Pin2);
  if (counter1 < 50) {
    //sensor 1
    if (HE_Raw1 < 325) {
      detect1 = true;
    } else {
      detect1 = false;
    }
    if ((detect1 != oldDetect1) && detect1) {
      currentTime1 = micros();
      short rpm1 = (60 * 1000000) / (currentTime1 - oldTime1);
      primaryRPM[counter1] = rpm1;
      primaryMicros[counter1] = currentTime1;
      counter1++;
      oldTime1 = currentTime1;
    }
    oldDetect1 = detect1;
  } else {
    saveRPMS();
  }

  //sensor 2
  if (counter2 < 50) {
    if (HE_Raw2 < 325) {
      detect2 = true;
    } else {
      detect2 = false;
    }
    if ((detect2 != oldDetect2) && detect2) {
      unsigned long currentTime2 = micros();
      short rpm2 = (60 * 1000000) / (currentTime2 - oldTime2);
      secondaryRPM[counter1] = rpm2;
      secondaryMicros[counter1] = currentTime2;
      counter2++;
      oldTime2 = currentTime2;
    } else {
      saveRPMS();
    }

    oldDetect2 = detect2;
  }
}

void saveRPMS() {
  myFile = SD.open("HEDATA.txt", FILE_WRITE);
  if (myFile) {
    if (counter1 == 50) {
      for (int i = 0; i < 50; i++) {
        myFile.print(primaryRPM[i]);
        myFile.print(",");
        myFile.println(primaryMicros[i]);
      }
      zeroPrimary();
    }
    if (counter2 == 50) {
      for (int i = 0; i < 50; i++) {
        myFile.print(secondaryRPM[i]);
        myFile.print(",");
        myFile.println(secondaryMicros[i]);
      }
      zeroSecondary();
    }
  }
  myFile.close();

}

void zeroPrimary()
{
  for (int i = 0; i < 50; i++) {
    primaryRPM[i] = 0;
    primaryMicros[i] = 0;
  }
  counter1 = 0;
}

void zeroSecondary() {
  for (int i = 0; i < 50; i++) {
    secondaryRPM[i] = 0;
    secondaryMicros[i] = 0;
  }
  counter2 = 0;
}
