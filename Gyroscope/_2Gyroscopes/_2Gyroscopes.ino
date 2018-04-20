/*  Krystal Bernal
 *  Last Updated: 4/19/18
 *  This code uses SPI communication to read two L3GD20H 3-Axis Gyroscopes
 */

#include <Adafruit_L3GD20_U.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>

#define CLK 9   //SCL
#define DO 8    //SA0
#define DI 7   //SDA
#define gyro1_CS 6
#define gyro2_CS 4

Adafruit_L3GD20 gyro1 = Adafruit_L3GD20(gyro1_CS, DO, DI, CLK);
Adafruit_L3GD20 gyro2 = Adafruit_L3GD20(gyro2_CS, DO, DI, CLK);

void setup(){
  Serial.begin(9600);
  if (!gyro1.begin(250)) {
    Serial.println("Error initializing gyro1.");
    while (1);
  }
  if (!gyro2.begin(250)) {
    Serial.println("Error initializing gyro2.");
    while (1);
  }
}

void loop(){
  gyro1.read();
  Serial.print("X: "); Serial.print((int)gyro1.data.x);
  Serial.print("   Y: "); Serial.print((int)gyro1.data.y);
  Serial.print("   Z: "); Serial.print((int)gyro1.data.z);

  gyro2.read();
  Serial.print("      X: "); Serial.print((int)gyro2.data.x);
  Serial.print("\tY: "); Serial.print((int)gyro2.data.y);
  Serial.print("\tZ: "); Serial.print((int)gyro2.data.z);
  
  Serial.println();
  delay(10);
}
