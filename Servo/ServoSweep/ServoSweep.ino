/* Krystal Bernal
    Last updated: 11/10/17

    This program sweeps two 180 degree servos

*/

#include <Servo.h>

#define servo1PIN 44
#define servo2PIN 45

Servo servo1;
Servo servo2;

void setup() {
  servo1.attach(servo1PIN);
  servo2.attach(servo2PIN);
  servo1.write(0);
  servo2.write(0);
}

void loop() {
  for (int i = 0; i <= 180, i++) {
    servo1.write(i);
    servo2.write(i);
  }
  delay(1000);
  for (int i = 180; i >= 0, i--) {
    servo1.write(i);
    servo2.write(i);
  }
  delay(1000);
}
