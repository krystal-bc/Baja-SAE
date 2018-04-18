/*  Krystal Bernal
 *  Last Updated: 3/29/2018
 *  
 *  This program reads data from two accelerometers
 *  
 *  https://learn.adafruit.com/adafruit-lis3dh-triple-axis-accelerometer-breakout/wiring-and-test
 */

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

#define CLK 13
#define MISO 12
#define MOSI 11
#define Acc1_CS 10
#define Acc2_CS 9

Adafruit_LIS3DH acc1 = Adafruit_LIS3DH(Acc1_CS, MOSI, MISO, CLK);
Adafruit_LIS3DH acc2 = Adafruit_LIS3DH(Acc2_CS, MOSI, MISO, CLK);

#if defined(ARDUINO_ARCH_SAMD)
   #define Serial SerialUSB
#endif

void setup(void) {
  Serial.begin(9600);
  
  if (!acc1.begin()) {
    Serial.println("Error initializing accelerometer 1");
    while (1);
  }
  if (!acc2.begin()){
    Serial.println("Error initializing accelerometer 2");
    while (1);
  }
  
  acc1.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!
  acc2.setRange(LIS3DH_RANGE_4_G);
}

void loop() {
  acc1.read();
  acc2.read();
  
  sensors_event_t event1; 
  acc1.getEvent(&event1);

  sensors_event_t event2; 
  acc2.getEvent(&event2);
  
  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("X: "); Serial.print(event1.acceleration.x);
  Serial.print("   Y: "); Serial.print(event1.acceleration.y); 
  Serial.print("   Z: "); Serial.print(event1.acceleration.z); 
  Serial.print("      X: "); Serial.print(event2.acceleration.x);
  Serial.print("   Y: "); Serial.print(event2.acceleration.y); 
  Serial.print("   Z: "); Serial.print(event2.acceleration.z);

  Serial.println();
 
  delay(10); 
}
