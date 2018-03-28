#include <Wire.h>
#include <SPI.h>
#include <Adafruit_L3GD20.h>
#include <Adafruit_Sensor.h>

Adafruit_L3GD20 gyro;

void setup() {
Serial.begin(9600);
  
  // Try to initialise and warn if we couldn't detect the chip
  if (!gyro.begin(gyro.L3DS20_RANGE_500DPS))
  {
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
