/* Krystal Bernal
    Last Updated: 3/29/2018

    This program reads data from two accelerometers and saves data to a microSD card

    SD needs its own set of communication pins
    DI = 11
    DO = 12
    SCK = 13

    https://learn.adafruit.com/adafruit-lis3dh-triple-axis-accelerometer-breakout/wiring-and-test
*/

#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

#define CLK 6 //SCL
#define MISO 5 //SDO
#define MOSI 4 //SDA
#define Acc1_CS 2
#define Acc2_CS 3
#define SD_CS 10

Adafruit_LIS3DH acc1 = Adafruit_LIS3DH(Acc1_CS, MOSI, MISO, CLK);
Adafruit_LIS3DH acc2 = Adafruit_LIS3DH(Acc2_CS, MOSI, MISO, CLK);

File myFile;
bool record;

long time;
long seconds;

#if defined(ARDUINO_ARCH_SAMD)
  #define Serial SerialUSB
#endif

void setup(void) {
  
  Serial.begin(9600);

  if (!acc1.begin()) {
    Serial.println("Error initializing accelerometer 1.");
  } else {
    Serial.println("Acc 1 initialized...");
  }
  if (!acc2.begin()) {
    Serial.println("Error initializing accelerometer 2.");
  } else {
    Serial.println("Acc 2 initialized...");
  }
  if (SD.begin(SD_CS)) {
    Serial.print("MicroSD card initialized...");
    myFile = SD.open("BAJADATA.txt", FILE_WRITE);
    if (myFile) {
      record = true;
      myFile.println("Acc1_X,Acc1_Y,Acc1_Z,Acc2_X,Acc2_Y,Acc2_Z,Seconds");
      Serial.println("Writing to BAJADATA.txt");
    }
  }else{
    Serial.println("Error initializing microSD card.");
  }
 
  acc1.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16G
  acc2.setRange(LIS3DH_RANGE_4_G);
}

void loop() {
  
  readAccel();
  time = millis();

  if (time > 10000) { //close after 10s
    myFile.close();
    Serial.println("BAJADATA.txt closed.");
    while (1);
  }
  delay(10);
}

void readAccel() {
  acc1.read();
  acc2.read();

  sensors_event_t event1;
  acc1.getEvent(&event1);
  
  sensors_event_t event2;
  acc2.getEvent(&event2);

  if (myFile) {
    record = true;
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
    myFile.println(event2.acceleration.z);
    myFile.print(",");
    myFile.println(time / 1000);
  }
  
  /* Display the results in m/s^2 */
  Serial.print("X: "); Serial.print(event1.acceleration.x);
  Serial.print("  Y: "); Serial.print(event1.acceleration.y);
  Serial.print("  Z: "); Serial.print(event1.acceleration.z);
  Serial.print("      X: "); Serial.print(event2.acceleration.x);
  Serial.print("   Y: "); Serial.print(event2.acceleration.y);
  Serial.print("   Z: "); Serial.print(event2.acceleration.z);

  Serial.println();
}
