/*
 * Written by Krystal Bernal and Jovanny Santana
 * for CSULA Baja SAE 2017-2018
 * Last Updated: 10/14/17
 * 
 * This program reads force in lbs from Load Cells and prints the readings to an LCD
*/

#include <WheatstoneBridge.h>
#include <LiquidCrystal.h>
#include <Servo.h>

WheatstoneBridge cell_1(A0, 365, 675, 0, 1000);
WheatstoneBridge cell_2(A1, 365, 675, 0, 1000);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int force1;
int force2;



unsigned int rpm1 = 0;        // RPM value
unsigned int rpm2 = 0;

unsigned long oldTime1 = 0;   // time value
unsigned long oldTime2 = 0;
unsigned long intTime1 = 60000000;   // time intervals
unsigned long intTime2 = 60000000;
int noAction = 0;

int servPos1;             // servo positions
int servPos2;

Servo rpmServo1;          // initialize servos
Servo rpmServo2;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  Serial.begin(112500);
  attachInterrupt(5, magnet1, RISING);    // pin 18 = sensor1 input
  attachInterrupt(4, magnet2, RISING);    // pin 19= sensor2 input
  rpmServo1.attach(44);                   // pin 44 = servo1 output
  rpmServo2.attach(46);                   // pin 45 = servo2 output
}

void loop() {
  printForces();
  readHallEffects();
}

void printForces(){
  
  force1 = cell_1.measureForce() * 0.49;
  force2 = cell_2.measureForce() * 0.49;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Load1:");
  lcd.setCursor(10, 0);
  lcd.print("Load2:");
  lcd.setCursor(0, 1);

  Serial.print("Load1: ");
  if (force1 > 0) {
    lcd.print(abs(force1), DEC);
    lcd.setCursor(4, 1);
    lcd.print("T");
    Serial.print(abs(force1), DEC);
    Serial.print(" T\t");
  } else {
    lcd.print(abs(force1), DEC);
    lcd.setCursor(4, 1);
    lcd.print("C");
    Serial.print(abs(force1), DEC);
    Serial.print(" C\t");
  }

  lcd.setCursor(10, 1);           // tab indent
  Serial.print("Load2: ");
  
  if (force2 > 0) {
    lcd.print("NoConn");           // delete when reading load 2
    Serial.print("NoConn");
    //lcd.print(abs(force2),DEC);
    //lcd.setCursor(15,1);
    //lcd.print("T");
    //Serial.print(abs(force2));
    //Serial.print(" T\t");
  } else {
    lcd.print("NoConn");           // delete when reading load 2
    //lcd.print(abs(force2),DEC);
    //lcd.setCursor(15,1);
    //lcd.print("C");
    //Serial.print(abs(force2));
    //Serial.print(" C\t");
  }
  delay(50);
}

void readHallEffects(){
  rpm1 = 60000000 / intTime1;   // rev/min = (60s/1min)*(60000ms/60s)*(1rev/timeIn(ms))
  rpm2 = 60000000 / intTime2;
  Serial.print("\tRPM 1: ");
  Serial.print(rpm1);
  Serial.print("\tRPM 2: ");
  Serial.println(rpm2);

  if (noAction > 10) {                    // if 10 loops pass with no magnetic detection
    rpm1 = 0;                             // reset servo positions to 0
    rpm2 = 0;
    noAction = 11;                        // prevent overflow of int
  }

  servPos1 = map(rpm1, 100, 1800, 160, 0);    // Servo1 range: 0 - 170
  servPos2 = map(rpm2, 100, 1800, 180, 20);   // Servo2 range: 20 - 180
  rpmServo1.write(servPos1);                  // set Servo1 to adjusted position
  rpmServo2.write(servPos2);                  // set Servo2 to adjusted position

  noAction++;
}

void magnet1() {                              // when magnet is detected
  intTime1 = micros() - oldTime1;             // update time interval
  oldTime1 = micros();                        // update starting point for timer1
  noAction = 0;                               // reset counter
}

void magnet2() {                              // when magnet is detected
  intTime2 = (micros() - oldTime2);           // update time interval
  oldTime2 = micros();                        // update starting point for timer2
  noAction = 0;                               // reset counter
}
