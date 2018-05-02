/*  Krystal Bernal
 *  Last Updated: 4/20/2018
 *  
 *  This program reads data from three LIS3DH accelerometers and 2 L3GD20H 3-Axis gyroscopes and saves data to a microSD card
 */

#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_L3GD20_U.h>

/* Daisy-chained communication pins
 * CLK = SCL
 * DO = SDO/SA0
 * DI = SDA
 */
#define SD_CS 10
#define CLK 9
#define DO 8
#define DI 7
#define gyro1_CS 6
#define Acc1_CS 5
#define gyro2_CS 4
#define Acc2_CS 3
#define Acc3_CS 2

#define LED1 A0
#define LED2 A1

Adafruit_LIS3DH acc1 = Adafruit_LIS3DH(Acc1_CS, DI, DO, CLK);
Adafruit_LIS3DH acc2 = Adafruit_LIS3DH(Acc2_CS, DI, DO, CLK);
Adafruit_LIS3DH acc3 = Adafruit_LIS3DH(Acc3_CS, DI, DO, CLK);
Adafruit_L3GD20 gyro1 = Adafruit_L3GD20(gyro1_CS, DO, DI, CLK);
Adafruit_L3GD20 gyro2 = Adafruit_L3GD20(gyro2_CS, DO, DI, CLK);

#if defined(ARDUINO_ARCH_SAMD)
   #define Serial SerialUSB
#endif

File myFile;
bool record;

long time;

void setup(void) {
  Serial.begin(9600);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  
  if (!acc1.begin()) {
    Serial.println("Error initializing accelerometer 1.");
    while (1);
  } else {
    Serial.println("Acc 1 initialized...");
  }
  if (!acc2.begin()) {
    Serial.println("Error initializing accelerometer 2.");
    while (1);
  } else {
    Serial.println("Acc 2 initialized...");
  }
  if (!acc3.begin()) {
    Serial.println("Error initializing accelerometer 3.");
    while (1);
  } else {
    Serial.println("Acc 3 initialized...");
  }
  if (!gyro1.begin(250)) {
    Serial.println("Error initializing gyro1.");
    while (1);
  }else {
    Serial.println("Gyro 1 initialized...");
  }
  if (!gyro2.begin(250)) {
    Serial.println("Error initializing gyro2.");
    while (1);
  }else {
    Serial.println("Gyro 2 initialized...");
  }
  digitalWrite(LED1, LOW);
  if (SD.begin(SD_CS)) {
    Serial.println("MicroSD card initialized...");
    digitalWrite(LED2, LOW);
    myFile = SD.open("BAJADATA.txt", FILE_WRITE);
    if (myFile) {
      record = true;
      myFile.println("Seconds,Acc1_X,Acc1_Y,Acc1_Z,Acc2_X,Acc2_Y,Acc2_Z,Acc3_X,Acc3_Y,Acc3_Z,Gyro1_X,Gyro1_Y,Gyro1_Z,Gyro2_X,Gyro2_Y,Gyro2_Z");
      Serial.println("Writing to BAJADATA.txt");
    }
  }else{
    Serial.println("Error initializing microSD card.");
  }
  
  acc1.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G
  acc2.setRange(LIS3DH_RANGE_4_G);
  acc3.setRange(LIS3DH_RANGE_4_G);
}

void loop() {
  time = millis();
  acc1.read();
  acc2.read();
  acc3.read();
  gyro1.read();
  gyro2.read();
  
  sensors_event_t event1; 
  acc1.getEvent(&event1);

  sensors_event_t event2; 
  acc2.getEvent(&event2);
  
  sensors_event_t event3; 
  acc3.getEvent(&event3);
  
  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("X: "); Serial.print(event1.acceleration.x);
  Serial.print("   Y: "); Serial.print(event1.acceleration.y); 
  Serial.print("   Z: "); Serial.print(event1.acceleration.z); 
  
  Serial.print("      X: "); Serial.print(event2.acceleration.x);
  Serial.print("   Y: "); Serial.print(event2.acceleration.y); 
  Serial.print("   Z: "); Serial.print(event2.acceleration.z);

  Serial.print("      X: "); Serial.print(event3.acceleration.x);
  Serial.print("   Y: "); Serial.print(event3.acceleration.y); 
  Serial.print("   Z: "); Serial.print(event3.acceleration.z);

  Serial.print("      X: "); Serial.print((int)gyro1.data.x);
  Serial.print("   Y: "); Serial.print((int)gyro1.data.y);
  Serial.print("   Z: "); Serial.print((int)gyro1.data.z);

  Serial.print("      X: "); Serial.print((int)gyro2.data.x);
  Serial.print("   Y: "); Serial.print((int)gyro2.data.y);
  Serial.print("   Z: "); Serial.print((int)gyro2.data.z);

  Serial.println();

  if (record) {
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
    myFile.print(event3.acceleration.x);
    myFile.print(",");
    myFile.print(event3.acceleration.y);
    myFile.print(",");
    myFile.print(event3.acceleration.z);
    myFile.print(",");
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
  }
  
  if (time > 10000) { //close after 10s
    myFile.close();
    //Serial.println("BAJADATA.txt closed.");
  }
 
  delay(10); 
}
