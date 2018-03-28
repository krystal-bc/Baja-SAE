#include <Wire.h>
#include <SPI.h>
#include <Adafruit_L3GD20.h>
#include <Adafruit_Sensor.h>

#define GYRO_CS 10 // labeled CS
#define GYRO_DO 12 // labeled SA0
#define GYRO_DI 11 // labeled SDA
#define GYRO_CLK 13// labeled SCL

//SPI (software)
Adafruit_L3GD20 gyro1(GYRO_CS, GYRO_DO, GYRO_DI, GYRO_CLK);
//I2C
Adafruit_L3GD20 gyro2;

void setup() {
Serial.begin(9600);
  if (!gyro1.begin(gyro1.L3DS20_RANGE_500DPS)){
    Serial.println("Gyro 1 (SPI) not detected");
    while (1);
  }
  if (!gyro2.begin(gyro2.L3DS20_RANGE_500DPS)){
    Serial.println("Gyro 2 (I2C) not detected");
    while (1);
  }
}

void loop() {
  //get raw x,y,z data:
  
  gyro1.read();
  gyro2.read();
  
  //print raw x,y,z data, in deg:
  
  //Gyro 1:
  Serial.println("Gyro 1 Deg: "); Serial.print("  X: "); Serial.print((float)gyro1.data.x); Serial.println(" deg ");
  Serial.print("  Y: "); Serial.print((float)gyro1.data.y); Serial.println(" deg ");
  Serial.print("  Z: "); Serial.print((float)gyro1.data.z); Serial.println(" deg ");
  //Gyro 2:
  Serial.println("Gyro 2 Deg: "); Serial.print("  X: "); Serial.println((float)gyro2.data.x);
  Serial.print("  Y:  "); Serial.println((float)gyro2.data.y); 
  Serial.print("  Z:  "); Serial.println((float)gyro2.data.z);

  //print in rad:

  //Gyro 1:
  Serial.println("Gyro 1 rad: "); Serial.print("  X: "); Serial.print((float)gyro1.data.x * SENSORS_DPS_TO_RADS); Serial.println(" rad ");
  Serial.print("  Y: "); Serial.print((float)gyro1.data.y * SENSORS_DPS_TO_RADS); Serial.println(" rad ");
  Serial.print("  Z: "); Serial.print((float)gyro1.data.z * SENSORS_DPS_TO_RADS); Serial.println(" rad ");
  //Gyro 2:
  Serial.println("Gyro 2 rad: "); Serial.print("  X: "); Serial.print((float)gyro2.data.x * SENSORS_DPS_TO_RADS); Serial.println(" rad ");
  Serial.print("  Y: "); Serial.print((float)gyro2.data.y * SENSORS_DPS_TO_RADS); Serial.println(" rad ");
  Serial.print("  Z: "); Serial.print((float)gyro2.data.z * SENSORS_DPS_TO_RADS); Serial.println(" rad ");

  Serial.println();
  delay(500);

}
