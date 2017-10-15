/*
 * Written by Krystal Bernal and Jovanny Santana
 * for CSULA Baja SAE 2017-2018
 * Last Updated: 10/14/17
 * 
 * This program uses hall effect sensors, magnets, and Servos
 * The magnets are placed on the drive and driven of a CVT
 * The hall effect sensors track when they complete a revolution
 * RPMs are calculated and displayed on Servos
*/

#include <Servo.h>

unsigned int rpm1;        // RPM value
unsigned int rpm2;

//can we use the clock for these? would there be a benefit in doing so?
unsigned long oldTime1;   // time value
unsigned long oldTime2;
unsigned long intTime1;   // time intervals
unsigned long intTime2;

int servPos1;             // servo positions
int servPos2;

Servo rpmServo1;          // initialize servos
Servo rpmServo2;

//Print these to the Serial Monitor
void setup(){
  Serial.begin(9600);
  attachInterrupt(5, magnet1, RISING);    // pin 18 = sensor1 input
  attachInterrupt(4, magnet2, RISING);    // pin 19 = sensor2 input
  rpmServo1.attach(44);                   // pin 44 = servo1 output
  rpmServo2.attach(45);                   // pin 45 = servo2 output
  rpm1 = 0;                               // initialize rpm1 to 0
  rpm2 = 0;                               // initialize rpm2 to 0
  oldTime1 = 0;                           // start temp timer1
  oldTime2 = 0;                           // start temp timer2
  intTime1 = 60000000;                    // initialize time1 interval
  intTime2 = 60000000;                    // initialize time2 interval
}

//create a method for this task
//i don't like the servo ranges. they should be true 0-180
void loop(){
  
  rpm1 = 60000000 / intTime1;   // rev/min = (60s/1min)*(60000ms/60s)*(1rev/timeIn(ms))
  rpm2 = 60000000 / intTime2;

  if (noAction > 10){                     // if 10 loops pass with no magnetic detection
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

void magnet1(){                               // when magnet is detected
  intTime1 = micros() - oldTime1;             // update time interval
  oldTime1 = micros();                        // update starting point for timer1
  noAction = 0;                               // reset counter
}

void magnet2(){                               // when magnet is detected
  intTime2 = (micros() - oldTime2);           // update time interval
  oldTime2 = micros();                        // update starting point for timer2
  noAction = 0;                               // reset counter
}
