// Basic demo for accelerometer readings from Adafruit LIS3DH
//https://learn.adafruit.com/adafruit-lis3dh-triple-axis-accelerometer-breakout/wiring-and-test

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

// Used for software SPI
#define CLK 13
#define MISO 12
#define MOSI 11
// Used for hardware & software SPI
#define Acc1_CS 10
#define Acc2_CS 10

// software SPI
Adafruit_LIS3DH acc1 = Adafruit_LIS3DH(Acc1_CS, MOSI, MISO, CLK);
Adafruit_LIS3DH acc2 = Adafruit_LIS3DH(Acc2_CS, MOSI, MISO, CLK);
// hardware SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS);
// I2C
//Adafruit_LIS3DH lis = Adafruit_LIS3DH();

#if defined(ARDUINO_ARCH_SAMD)
   #define Serial SerialUSB
#endif

void setup(void) {
  Serial.begin(9600);
  
  if (!acc1.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Error initializing accelerometer 1");
    while (1);
  }
  if (!acc2.begin(0x19)){
    Serial.println("Error initializing accelerometer 2");
    while (1);
  }
  
  acc1.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!
  acc2.setRange(LIS3DH_RANGE_4_G);
}

void loop() {
  acc1.read();

  /* Or....get a new sensor event, normalized */ 
  sensors_event_t event1; 
  acc1.getEvent(&event1);

  sensors_event_t event2; 
  acc1.getEvent(&event2);
  
  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("\t\tX: "); Serial.print(event1.acceleration.x);
  Serial.print(" \tY: "); Serial.print(event1.acceleration.y); 
  Serial.print(" \tZ: "); Serial.print(event1.acceleration.z); 
  Serial.print("\t\tX: "); Serial.print(event2.acceleration.x);
  Serial.print(" \tY: "); Serial.print(event2.acceleration.y); 
  Serial.print(" \tZ: "); Serial.print(event2.acceleration.z);

  Serial.println();
 
  delay(10); 
}
