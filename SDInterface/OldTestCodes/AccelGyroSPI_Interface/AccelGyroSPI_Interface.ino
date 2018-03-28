#include <Adafruit_L3GD20.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11
#define LIS3DH_CS 10

#define GYRO_CS 4 //labeled CS
#define GYRO_DO 5 //labeled SAO
#define GYRO_DI 6 //labeled SDA
#define GYRO_CLK 7 //labeled SCL

Adafruit_L3GD20 gyro1(GYRO_CS, GYRO_DO, GYRO_DI, GYRO_CLK);
Adafruit_LIS3DH lis1 = Adafruit_LIS3DH(LIS3DH_CS, LIS3DH_MOSI, LIS3DH_MISO, LIS3DH_CLK);

void setup() {
Serial.begin(9600);
   if (!gyro1.begin(gyro1.L3DS20_RANGE_500DPS)){
      Serial.println("Gyro 1 not detected");
      while (1);
   }
    if (! lis1.begin(0x18)) {   // change this to 0x19 for alternative i2c address
      Serial.println("Accel 1 not found");
      while (1);
   }

  lis1.setRange(LIS3DH_RANGE_8_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis1.getRange());  
  Serial.println("G");

}

void loop() {
  // put your main code here, to run repeatedly:

}
