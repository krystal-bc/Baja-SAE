/* Krystal Bernal
 * Last Updated: 3-19-18
 * 
 * This code uses I2C connections for a L3GD20H 3-axis gyroscope
 */

 //use adafruit library https://github.com/adafruit/Adafruit_L3GD20_U
 //use library manager to get adafruit sensor library
#include <Wire.h> 
#include <Adafruit_L3GD20.h>

//remove when using SPI
#define USE_I2C

#ifdef USE_I2C
  Adafruit_L3GD20 gyro;
#else
  //define for SPI
  //https://www.arduino.cc/en/Reference/SPI
  #define GYRO_CS 4 // labeled CS
  #define GYRO_DO 5 // labeled SA0
  #define GYRO_DI 6  // labeled SDA
  #define GYRO_CLK 7 // labeled SCL
  Adafruit_L3GD20 gyro(GYRO_CS, GYRO_DO, GYRO_DI, GYRO_CLK);
#endif

/*
L3DS20_RANGE_250DPS - for 250 degrees-per-second range (default)
L3DS20_RANGE_500DPS - for 500 degrees-per-second range
L3DS20_RANGE_2000DPS - for 2000 degrees-per-second range
*/
void setup(){
  Serial.begin(9600);
  if(!gyro.begin(gyro.L3DS20_RANGE_250DPS)){//compiler doesn't like this?
    Serial.println("Error initializing gyro");
    while (1);
  }
}

void loop(){
  //values are in degrees per second
  //#define SENSORS_DPS_TO_RADS (0.017453293F)  // converts to rad/s
  //(int)gyro.data.x * SENSORS_DPS_TO_RADS;     //implementation of conversion factor
  gyro.read();
  Serial.print("X: "); Serial.print((int)gyro.data.x);   Serial.print(" ");
  Serial.print("Y: "); Serial.print((int)gyro.data.y);   Serial.print(" ");
  Serial.print("Z: "); Serial.println((int)gyro.data.z); Serial.print(" ");
  delay(100);
}
