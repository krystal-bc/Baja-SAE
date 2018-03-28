#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11
#define LIS3DH_CS 10

//SPI (software)
Adafruit_LIS3DH lis1 = Adafruit_LIS3DH(LIS3DH_CS, LIS3DH_MOSI, LIS3DH_MISO, LIS3DH_CLK);
//I2C
Adafruit_LIS3DH lis2 = Adafruit_LIS3DH();

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif


void setup() {
   #ifndef ESP8266
     while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
   #endif


  Serial.begin(9600);
  Serial.println("LIS3DH test!");


  if (! lis1.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("LIS3DH #1 found!");


   if (! lis2.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("LIS3DH #2 found!");


  lis1.setRange(LIS3DH_RANGE_8_G);   // 2, 4, 8 or 16 G for accel 1 (the SPI one)
  lis2.setRange(LIS3DH_RANGE_8_G);   // 2, 4, 8 or 16 G for accel 2 (the I2C one)
  Serial.print("Range for accel 1 = "); Serial.print(2 << lis1.getRange());  
  Serial.println("G");
  Serial.print("Range for accel 2 = "); Serial.print(2 << lis2.getRange());  
  Serial.println("G");
}

void loop() {
  //get raw x,y,z data:
  
  lis1.read();
  lis2.read();
  
  //print raw x,y,z data:
  
  //Accel 1:
  Serial.println("Accel 1 Raw: "); Serial.print("  X: "); Serial.println(lis1.x);
  Serial.print("  Y: "); Serial.println(lis1.y); 
  Serial.print("  Z: "); Serial.println(lis1.z);
  //Accel 2:
  Serial.println("Accel 2 Raw: "); Serial.print("  X: "); Serial.println(lis1.x);
  Serial.print("  Y:  "); Serial.println(lis1.y); 
  Serial.print("  Z:  "); Serial.println(lis1.z);


  //normalize raw data
  sensors_event_t event1; 
  lis1.getEvent(&event1);
  sensors_event_t event2; 
  lis2.getEvent(&event2);
  
  //print in m/s^2:

  //Accel 1:
  Serial.println("Accel 1 m/s^2: "); Serial.print("  X: "); Serial.print(event1.acceleration.x); Serial.println(" m/s^2 ");
  Serial.print("  Y: "); Serial.print(event1.acceleration.y); Serial.println(" m/s^2 ");
  Serial.print("  Z: "); Serial.print(event1.acceleration.z); Serial.println(" m/s^2 ");
  //Accel 2:
  Serial.println("Accel 2 m/s^2: "); Serial.print("  X: "); Serial.print(event2.acceleration.x); Serial.println(" m/s^2 ");
  Serial.print("  Y: "); Serial.print(event2.acceleration.y); Serial.println(" m/s^2 ");
  Serial.print("  Z: "); Serial.print(event2.acceleration.z); Serial.println(" m/s^2 ");

  Serial.println();
  delay(500);

}


