/*  Krystal Bernal
    Last Updated: 4/20/2018

    This program reads data from three LIS3DH accelerometers and 2 L3GD20H 3-Axis gyroscopes and saves data to a microSD card
*/

#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_L3GD20_U.h>

/* Daisy-chained communication pins
   CLK = SCL
   DO = SDO/SA0
   DI = SDA
*/
#define SD_CS 10
#define CLK 4
#define DO 3
#define DI 2
#define gyro1_CS 9
#define Acc1_CS 8
#define gyro2_CS 6
#define Acc2_CS 7
//#define Acc3_CS 2

#define LED1 A0
#define LED2 A1
#define LED3 A3

Adafruit_LIS3DH acc1 = Adafruit_LIS3DH(Acc1_CS, DI, DO, CLK);
Adafruit_LIS3DH acc2 = Adafruit_LIS3DH(Acc2_CS, DI, DO, CLK);
//Adafruit_LIS3DH acc3 = Adafruit_LIS3DH(Acc3_CS, DI, DO, CLK);
Adafruit_L3GD20 gyro1 = Adafruit_L3GD20(gyro1_CS, DO, DI, CLK);
Adafruit_L3GD20 gyro2 = Adafruit_L3GD20(gyro2_CS, DO, DI, CLK);

#if defined(ARDUINO_ARCH_SAMD)
#define Serial SerialUSB
#endif

File myFile;

unsigned long time;

void setup(void) {
  Serial.begin(9600);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);


  if (acc1.begin() && acc2.begin() && gyro1.begin(250) && gyro2.begin(250)) {
    //acc3.begin();
    digitalWrite(LED1, LOW);
  }
  if (SD.begin(SD_CS)) {
    digitalWrite(LED2, LOW);
    myFile = SD.open("BAJADATA.txt", FILE_WRITE);
    if (myFile) {
      myFile.println("micros,Acc1_X,Acc1_Y,Acc1_Z,Acc2_X,Acc2_Y,Acc2_Z,Gyro1_X,Gyro1_Y,Gyro1_Z,Gyro2_X,Gyro2_Y,Gyro2_Z");
    }
  }

  acc1.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G
  acc2.setRange(LIS3DH_RANGE_4_G);
  //  acc3.setRange(LIS3DH_RANGE_4_G);
}

void loop() {
  time = micros();
  acc1.read();
  acc2.read();
  //  acc3.read();
  gyro1.read();
  gyro2.read();

  sensors_event_t event1;
  acc1.getEvent(&event1);

  sensors_event_t event2;
  acc2.getEvent(&event2);

  //  sensors_event_t event3;
  //  acc3.getEvent(&event3);
  myFile = SD.open("BAJADATA.txt", FILE_WRITE);
  if (myFile) {
    myFile.print(time);
    myFile.print(",");
    myFile.print(event1.acceleration.x);
    myFile.print(",");
    myFile.print(event1.acceleration.y);
    myFile.print(",");
    myFile.print(event1.acceleration.z);
    myFile.print(",");
    myFile.print(event2.acceleration.x);
    myFile.print(",");
    myFile.print(event2.acceleration.y);
    myFile.print(",");
    myFile.print(event2.acceleration.z);
    myFile.print(",");
    //    myFile.print(event3.acceleration.x);
    //    myFile.print(",");
    //    myFile.print(event3.acceleration.y);
    //    myFile.print(",");
    //    myFile.print(event3.acceleration.z);
    //    myFile.print(",");
    myFile.print((int)gyro1.data.x);
    myFile.print(",");
    myFile.print((int)gyro1.data.y);
    myFile.print(",");
    myFile.print((int)gyro1.data.z);
    myFile.print(",");
    myFile.print((int)gyro2.data.x);
    myFile.print(",");
    myFile.print((int)gyro2.data.y);
    myFile.print(",");
    myFile.print((int)gyro2.data.z);

    myFile.println();
    myFile.close();

  }

}
