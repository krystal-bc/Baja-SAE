/* Krystal Bernal
 * Last Updated: 3-19-18
 * 
 * This code uses I2C connections for a L3GD20H 3-axis gyroscope
 */

 //use adafruit library https://github.com/adafruit/Adafruit_L3GD20_U
 //use library manager to get adafruit sensor library
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_L3GD20_U.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_L3GD20_Unified gyro = Adafruit_L3GD20_Unified(20);

void setup (){
  Serial.begin(9600);  
  gyro.enableAutoRange(true); //Enable auto-ranging
  if(!gyro.begin()){
    Serial.println("Gyro failed to initialize");
    while(1);
  }
  displaySensorDetails();
}

void loop() {
  /* Get a new sensor event */ 
  sensors_event_t event; 
  gyro.getEvent(&event);
 
  /* Display results in rad/s */
  Serial.print("X: "); Serial.print(event.gyro.x); Serial.print("\t");
  Serial.print("Y: "); Serial.print(event.gyro.y); Serial.print("\t");
  Serial.print("Z: "); Serial.print(event.gyro.z); Serial.print("\t");
  Serial.println("rad/s ");
  delay(10);
}

void displaySensorDetails(){
  sensor_t sensor;
  gyro.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" rad/s");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" rad/s");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" rad/s");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}
