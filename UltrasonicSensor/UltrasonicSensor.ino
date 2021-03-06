/* 
 *  Krystal Bernal
 *  Last Updated: 10/30/18
 *  
 *  This code prints time elapsed and the reading of a 4-pin ultrasonic sensor.
 *  
 *  HC-SR04 Sensor
 *  https://www.dealextreme.com/p/hc-sr04-ultrasonic-sensor-distance-measuring-module-133696
 *  An HC-SR04 ultrasonic sensor receives a pulse to initiate a reading, then listens for a pulse 
 *  to return.  The length of the returning pulse is proportional to 
 *  the distance of the object from the sensor.
 */
#include <SPI.h>
#include <SD.h>

#define SD_CS 10
#define echoPin 9
#define trigPin 8
//#define LED 7


File myFile;

long duration;
float inches;

void setup() {
  //Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  if (SD.begin(SD_CS)) {
    //digitalWrite(LED, LOW);
    //Serial.println("SD initialized");
    myFile = SD.open("ULTRASNC.txt", FILE_WRITE);
    if (myFile) {
      myFile.println("micros, inches");
      //Serial.println("File accessed");
    }
  }
}

void loop(){
  
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);

//  Serial.print(micros());
//  Serial.print("   ");
//  Serial.print(inches);
//  Serial.print("in");
//  Serial.println();

  myFile = SD.open("ULTRASNC.txt", FILE_WRITE);
  if (myFile) {
    myFile.print(micros());
    myFile.print(",");
    myFile.print(inches);
    myFile.println();
    myFile.close();
  }
  delay(100);
}

float microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING, there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74.0 / 2.0;
}

float microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29.0 / 2.0;
}
