#include <Adafruit_L3GD20.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LIS3DH.h>
#include <Wire.h>
#include <SPI.h>

Adafruit_LIS3DH lis2 = Adafruit_LIS3DH();
Adafruit_L3GD20 gyro2;

void setup() {
Serial.begin(9600);

  if (! lis2.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("LIS3DH #2 found!");

    if (!gyro2.begin(gyro2.L3DS20_RANGE_500DPS)){
    Serial.println("Gyro 2 (I2C) not detected");
    while (1);
  }

  lis2.setRange(LIS3DH_RANGE_8_G);   // 2, 4, 8 or 16 G for accel 2 (the I2C one)
  Serial.print("Range for accel 2 = "); Serial.print(2 << lis2.getRange());  
  Serial.println("G");
}

void loop() {
  //get raw accel data & print it
  lis2.read();
  Serial.println("Accel 2 Raw: "); Serial.print("  X: "); Serial.println(lis2.x);
  Serial.print("  Y:  "); Serial.println(lis2.y); 
  Serial.print("  Z:  "); Serial.println(lis2.z);
  //get raw gyro data and print it
  gyro2.read();
  Serial.print("X: "); Serial.print((float)gyro2.data.x);   Serial.print("deg ");
  Serial.print("Y: "); Serial.print((float)gyro2.data.y);   Serial.print("deg ");
  Serial.print("Z: "); Serial.print((float)gyro2.data.z);   Serial.println("deg ");

}




