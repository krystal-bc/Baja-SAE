/* Created by: Sidra Gibeault
 * Baja SAE 2017-2018
 * 
 * Description: This code allows for interface between 2 gyroscopes and 2 accelerometers through the 
 * 2 available data lines on an arduino mega. There is one accelerometer and one gyroscope
 * connected to each of the SPI and I2C communication lines, and 2 sd cards read data from 
 * these 2 lines simultaneously and name files according to how many microseconds it has 
 * been since the arduino started. Both SD cards are connected to the same SPI line and are 
 * differentiated by their card select pins.
 * 
 * Pinout on an Arduino Mega: DI/SDA on both SD cards to 51, SCL/SCK on both SD cards to 52,
 * DO/SDO on both SD cards to 50, CS on one SD card to 48 and the other to 53 (this is arbitrary), 
 * SCL on Gyro1 to 7, SDA on Gyro1 to 6, SAO on Gyro1 to 5, CS on Gyro1 to 4, 
 * SCL on Accel1 to 13, SDA on Accel1 to 11, SDO on Accel1 to 12, CS on Accel1 to 10,
 * SCL on Accel2 and Gyro2 to 21, SDA on Accel2 and Gyro2 to 20, and all Vin/Gnd pins 
 * to the 5V or Gnd on the arduino. Accel1 and Gyro1 use SPI, while Accel2 and Gyro2 I2C. 
 * The sensors used in this project are Adafruit LIS3DH and Adafruit L3GD20H. 
 * 
 * Note: it is not recommended that you use 2 SD cards simultaneously on an arduino uno due 
 * to the amount of RAM required. Keep in mind that the pinout for this project is different
 * on uno because its spi and i2c pins are different and that the uno may crash when using 
 * 2 sd cards. SdFat library is used to support use of multiple cards.
 * 
 * Troubleshooting: if one SD card isn't initializing, try switching the CS pins on the SD cards. 
 * This worked for me though I am still researching the reasoning behind this. If this doesn't work, 
 * try switching the SD cards or restarting the arduino board.
 * 
 * TODO: use button to control recording and LED to indicate, similar to previous baja code.
 */
#include <Adafruit_L3GD20.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include "SdFat.h"
#include "FreeStack.h"

#if defined(ARDUINO_ARCH_SAMD)
#define Serial SerialUSB
#endif

//SPI

#define LIS3DH_CLK 13 //labeled SCL
#define LIS3DH_MISO 12 //labeled SDO
#define LIS3DH_MOSI 11 //labeled SDA
#define LIS3DH_CS 10 //labeled CS

#define GYRO_CS 4 //labeled CS
#define GYRO_DO 5 //labeled SAO
#define GYRO_DI 6 //labeled SDA
#define GYRO_CLK 7 //labeled SCL

Adafruit_L3GD20 gyro1(GYRO_CS, GYRO_DO, GYRO_DI, GYRO_CLK);
Adafruit_LIS3DH lis1 = Adafruit_LIS3DH(LIS3DH_CS, LIS3DH_MOSI, LIS3DH_MISO, LIS3DH_CLK);

//I2C

//connect both SDA pins to 20, connect both SCL pins to 21.
Adafruit_LIS3DH lis2 = Adafruit_LIS3DH();
Adafruit_L3GD20 gyro2;

//SD Card

SdFile myFile;
//both filenames are the amt of microseconds since arduino started
char filename1[35];
char filename2[35];
String file = "";

SdFat sd1;
const uint8_t SD1_CS = 48;  // chip select for sd1

SdFat sd2;
const uint8_t SD2_CS = 53;   // chip select for sd2

const uint8_t BUF_DIM = 100;
uint8_t buf[BUF_DIM];

const uint32_t FILE_SIZE = 1000000;
const uint16_t NWRITE = FILE_SIZE/BUF_DIM;
//------------------------------------------------------------------------------
// print error msg, any SD error codes, and halt.
// store messages in flash
#define errorExit(msg) errorHalt(F(msg))
#define initError(msg) initErrorHalt(F(msg))
//------------------------------------------------------------------------------

float gyro1x;
float gyro1y;
float gyro1z;
float gyro2x;
float gyro2y;
float gyro2z;
float accel1x;
float accel1y;
float accel1z;
float accel2x;
float accel2y;
float accel2z;

void setup() {
  Serial.begin(9600);
  // Wait for USB Serial 
  while (!Serial) {
    SysCall::yield();
  }   
   if (! lis1.begin(0x18)) {   // change this to 0x19 for alternative i2c address
      Serial.println("Accel 1 not found");
      while (1);}
   Serial.println("Accel #1 found!");
   
   if (! lis2.begin(0x18)) {   // change this to 0x19 for alternative i2c address
     Serial.println("Accel 2 not found");
     while (1); }
   Serial.println("Accel #2 found!");
   
   if (!gyro1.begin(gyro1.L3DS20_RANGE_500DPS)){
      Serial.println("Gyro 1 not detected");
      while (1);}
   Serial.println("Gyro #1 found!");
   
   if (!gyro2.begin(gyro2.L3DS20_RANGE_500DPS)){
     Serial.println("Gyro 2 not detected");
     while (1);}
   Serial.println("Gyro #2 found!");
 
  lis1.setRange(LIS3DH_RANGE_8_G);   // 2, 4, 8 or 16 G!
  Serial.print("Range for accel 1 = "); Serial.print(2 << lis1.getRange());  
  Serial.println("G");
  lis2.setRange(LIS3DH_RANGE_8_G);   // 2, 4, 8 or 16 G for accel 2 (the I2C one)
  Serial.print("Range for accel 2 = "); Serial.print(2 << lis2.getRange());  
  Serial.println("G");

  Serial.println("Sensors initialized");
  
  //begin sd card directory making
  Serial.println(F("Type any character to start SD file prepping"));
    while (!Serial.available()) {
    SysCall::yield();
  }

  // disable sd2 while initializing sd1
  pinMode(SD2_CS, OUTPUT);
  digitalWrite(SD2_CS, HIGH);

  // initialize the first card
  if (!sd1.begin(SD1_CS)) {
    sd1.initError("sd1:");
  }
  Serial.println("Card 1 initialized!");
  // create Test1 on sd1 if it does not exist. if it does, create the next test.
  if(!sd1.exists("/Test1")){
    if (!sd1.mkdir("/Test1")) {
      sd1.errorExit("sd1.mkdir");
    }
    if (!sd1.chdir("/Test1")) {
    sd1.errorExit("sd1.chdir");
    }
    Serial.println("Test1 folder created on card 1");
  }
  else if(!sd1.exists("/Test2")){
    if (!sd1.mkdir("/Test2")) {
      sd1.errorExit("sd1.mkdir");
    }
    if (!sd1.chdir("/Test2")) {
    sd1.errorExit("sd1.chdir");
    }
    Serial.println("Test2 folder created on card 1");
  }
  else if(!sd1.exists("/Test3")){
    if (!sd1.mkdir("/Test3")) {
      sd1.errorExit("sd1.mkdir");
    }
    if (!sd1.chdir("/Test3")) {
    sd1.errorExit("sd1.chdir");
  }
    Serial.println("Test3 folder created on card 1");
  }
  else if(!sd1.exists("/Test4")){
    if (!sd1.mkdir("/Test4")) {
      sd1.errorExit("sd1.mkdir");
    }
    if (!sd1.chdir("/Test4")) {
    sd1.errorExit("sd1.chdir");
  }
    Serial.println("Test4 folder created on card 1");
  }
  else if(!sd1.exists("/Test5")){
    if (!sd1.mkdir("/Test5")) {
      sd1.errorExit("sd1.mkdir");
    }
    if (!sd1.chdir("/Test5")) {
    sd1.errorExit("sd1.chdir");
  }
    Serial.println("Test5 folder created on card 1");
  }
  else {(sd1.errorExit("Error: too many directories on SD Card 1."));}
  // initialize the second card
  if (!sd2.begin(SD2_CS)) {
    sd2.initError("sd2:");
  }
  Serial.println("Card 2 initialized!");
   if(!sd2.exists("/Test1")){
    if (!sd2.mkdir("/Test1")) {
      sd2.errorExit("sd2.mkdir");
    }
    if (!sd2.chdir("/Test1")) {
    sd2.errorExit("sd2.chdir");
  }
    Serial.println("Test1 folder created on card 2");
  }
  else if(!sd2.exists("/Test2")){
    if (!sd2.mkdir("/Test2")) {
      sd2.errorExit("sd2.mkdir");
    }
    if (!sd2.chdir("/Test2")) {
    sd2.errorExit("sd2.chdir");
  }
    Serial.println("Test2 folder created on card 2");
  }
  else if(!sd2.exists("/Test3")){
    if (!sd2.mkdir("/Test3")) {
      sd2.errorExit("sd2.mkdir");
    }
    if (!sd2.chdir("/Test3")) {
    sd2.errorExit("sd2.chdir");
  }
    Serial.println("Test3 folder created on card 2");
  }
  else if(!sd2.exists("/Test4")){
    if (!sd2.mkdir("/Test4")) {
      sd2.errorExit("sd2.mkdir");
    }
    if (!sd2.chdir("/Test4")) {
    sd2.errorExit("sd2.chdir");
  }
    Serial.println("Test4 folder created on card 2");
  }
  else if(!sd2.exists("/Test5")){
    if (!sd2.mkdir("/Test5")) {
      sd2.errorExit("sd2.mkdir");
    }
    if (!sd2.chdir("/Test5")) {
    sd2.errorExit("sd2.chdir");
  }
    Serial.println("Test5 folder created on card 2");
  }
  else {(sd2.errorExit("Error: too many directories on SD Card 2."));}

  //we just created a folder (directory) on each card for each test. Then we can save data to it in the loop function.

  Serial.println("Setup Complete.");
}

void loop() {
  

//ACCELEROMETERS

  
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
  accel1x = event1.acceleration.x;
  accel1y = event1.acceleration.y;
  accel1z = event1.acceleration.z;
  //Accel 2:
  Serial.println("Accel 2 m/s^2: "); Serial.print("  X: "); Serial.print(event2.acceleration.x); Serial.println(" m/s^2 ");
  Serial.print("  Y: "); Serial.print(event2.acceleration.y); Serial.println(" m/s^2 ");
  Serial.print("  Z: "); Serial.print(event2.acceleration.z); Serial.println(" m/s^2 ");
  accel2x = event2.acceleration.x;
  accel2y = event2.acceleration.y;
  accel2z = event2.acceleration.z;

  Serial.println();
  delay(1);


//GYROSCOPES


  //get raw x,y,z data:
  
  gyro1.read();
  gyro2.read();
  
  //print raw x,y,z data, in deg:
  
  //Gyro 1:
  Serial.println("Gyro 1 Deg: "); Serial.print("  X: "); Serial.print((float)gyro1.data.x); Serial.println(" deg ");
  Serial.print("  Y: "); Serial.print((float)gyro1.data.y); Serial.println(" deg ");
  Serial.print("  Z: "); Serial.print((float)gyro1.data.z); Serial.println(" deg ");
  gyro1x = (float)gyro1.data.x;
  gyro1y = (float)gyro1.data.y;
  gyro1z = (float)gyro1.data.z;
  //Gyro 2:
  Serial.println("Gyro 2 Deg: "); Serial.print("  X: "); Serial.println((float)gyro2.data.x);
  Serial.print("  Y:  "); Serial.println((float)gyro2.data.y); 
  Serial.print("  Z:  "); Serial.println((float)gyro2.data.z);  
  gyro2x = (float)gyro2.data.x;
  gyro2y = (float)gyro2.data.y;
  gyro2z = (float)gyro2.data.z;

  //Gyro 1:
  Serial.println("Gyro 1 rad: "); Serial.print("  X: "); Serial.print((float)gyro1.data.x * SENSORS_DPS_TO_RADS); Serial.println(" rad ");
  Serial.print("  Y: "); Serial.print((float)gyro1.data.y * SENSORS_DPS_TO_RADS); Serial.println(" rad ");
  Serial.print("  Z: "); Serial.print((float)gyro1.data.z * SENSORS_DPS_TO_RADS); Serial.println(" rad ");
  //Gyro 2:
  Serial.println("Gyro 2 rad: "); Serial.print("  X: "); Serial.print((float)gyro2.data.x * SENSORS_DPS_TO_RADS); Serial.println(" rad ");
  Serial.print("  Y: "); Serial.print((float)gyro2.data.y * SENSORS_DPS_TO_RADS); Serial.println(" rad ");
  Serial.print("  Z: "); Serial.print((float)gyro2.data.z * SENSORS_DPS_TO_RADS); Serial.println(" rad ");

  Serial.println();


//READ TO SD CARD


  //create the file names:
  file += String(micros());
  file += ".txt";
  int n = file.length();
  char char_array[n+1];
  strcpy(char_array, file.c_str());
  for(int i=0; i<n; i++){
    filename1[i] = char_array[i];
    filename2[i] = char_array[i];
  }
  sd1.chvol();
  //default directory set to sd card 1
  SdFile file1;
  //if the file doesn't exist, create it. if it does, truncate it to 0 length.
  if (!file1.open(filename1, O_RDWR | O_CREAT | O_TRUNC)) {
    sd1.errorExit("file1 not created");
  }
  //the data will be printed in the file in the order it is listed in the heading:
  Serial.println(F("Writing to sd1"));
  file1.println(filename1);
  file1.println("Accel1 x,y,z. Gyro1 x,y,z."); //make sure heading matches values
  file1.println(accel1x);
  file1.println(accel1y);
  file1.println(accel1z);
  file1.println(gyro1x);
  file1.println(gyro1y);
  file1.println(gyro1z);
  //make sure the data just returned matches that saved to the sd card. if not, exit with error:
  if (!file1.sync() || file1.getWriteError()) {
    sd1.errorExit("write error");
  }
  Serial.println("Data written to sd1 successfully.");
  file1.close();
  //need to close this file before attempting to write to a new sd card
  
  sd2.chvol();
  //default directory set to sd card 2
  SdFile file2;
  //if the file doesn't exist, create it. if it does, truncate it to 0 length.
  if (!file2.open(filename2, O_RDWR | O_CREAT | O_TRUNC)) {
    sd2.errorExit("file2 not created");
  }
  //the data will be printed in the file in the order it is listed in the heading:
  Serial.println(F("Writing to sd2"));
  file2.println(filename2);
  file2.println("Accel2 x,y,z. Gyro2 x,y,z."); //make sure heading matches values
  file2.println(accel2x);
  file2.println(accel2y);
  file2.println(accel2z);
  file2.println(gyro2x);
  file2.println(gyro2y);
  file2.println(gyro2z);
  //make sure the data just returned matches that saved to the sd card. if not, exit with error:
  if (!file2.sync() || file2.getWriteError()) {
    sd2.errorExit("write error");
  }
  Serial.println("Data written to sd2 successfully.");
  file2.close();

  //must reset the file name to nothing after the loop is complete. Otherwise, the next file name will
  //be added onto the end of the string.
  for(int i=0; i<n; i++){
    filename1[i] = '\0';
    filename2[i] = '\0';
  }
  file = "";
  
}
