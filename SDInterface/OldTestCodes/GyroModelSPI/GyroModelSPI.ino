#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_L3GD20.h>

#define GYRO_CS 10 // labeled CS
#define GYRO_DO 12 // labeled SA0
#define GYRO_DI 11 // labeled SDA
#define GYRO_CLK 13// labeled SCL
Adafruit_L3GD20 gyro(GYRO_CS, GYRO_DO, GYRO_DI, GYRO_CLK);

void setup() {
Serial.begin(9600);
  // Try to initialise and warn if we couldn't detect the chip
   if (!gyro.begin(gyro.L3DS20_RANGE_500DPS)){
      Serial.println("Oops ... unable to initialize the L3GD20. Check your wiring!");
      while (1);
   }
}

void loop() {
 gyro.read();
  Serial.print("X: "); Serial.print((float)gyro.data.x);   Serial.print("deg ");
  Serial.print("Y: "); Serial.print((float)gyro.data.y);   Serial.print("deg ");
  Serial.print("Z: "); Serial.print((float)gyro.data.z);   Serial.println("deg ");

  Serial.print("X: "); Serial.print((float)gyro.data.x * SENSORS_DPS_TO_RADS);   Serial.print("rad ");
  Serial.print("Y: "); Serial.print((float)gyro.data.y * SENSORS_DPS_TO_RADS);   Serial.print("rad ");
  Serial.print("Z: "); Serial.print((float)gyro.data.z * SENSORS_DPS_TO_RADS);   Serial.println("rad ");
  delay(100);
}
