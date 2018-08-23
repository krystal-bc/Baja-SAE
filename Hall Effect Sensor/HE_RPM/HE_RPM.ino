/*
   Krystal Bernal
   CSULA Baja SAE
   Last Updated: 8/16/18

   This code uses hall effect sensors and revolving magnets as tachometers for
   reading rpm of drive and driven on a CVT. Ratio is used for tuning.

   Previous code used built-in Arduino interrupt, but was unreliable. According to Arduino's
   documentation: "millis() relies on interrupts to count, so it will never increment inside an ISR.
   micros() works initially, but will start behaving erratically after 1-2 ms."
*/

//max fan rpm = 4000

#define HE_Pin1 A4
#define HE_Pin2 A3

unsigned long currentTime1 = 0;
unsigned long oldTime1 = 0;

bool detect1 = false;
bool oldDetect1 = false;

unsigned long currentTime2 = 0;
unsigned long oldTime2 = 0;

int rpm1 = 0;
int rpm2 = 0;

double ratio = 0;

bool detect2 = false;
bool oldDetect2 = false;

void setup() {
  Serial.begin(115200);
  pinMode(HE_Pin1, INPUT);
  pinMode(HE_Pin2, INPUT);
}

void loop() {
  int HE_Raw1 = analogRead(HE_Pin1);
  int HE_Raw2 = analogRead(HE_Pin2);

  //Serial.print(HE_Raw1);

  //sensor 1
  //update these values dynamically
  if (HE_Raw1 < 250) {
    detect1 = true;
  } else {
    detect1 = false;
  }
  if ((detect1 != oldDetect1) && detect1) {
    currentTime1 = micros();
    rpm1 = (60 * 1000000) / (currentTime1 - oldTime1);
    Serial.print("RPM 1: ");
    Serial.print(rpm1);
    oldTime1 = currentTime1;
  }

  oldDetect1 = detect1;

  //sensor 2 
  if (HE_Raw2 < 250) {
    detect2 = true;
  } else {
    detect2 = false;
  }
  if ((detect2 != oldDetect2) && detect2) {
    currentTime2 = micros();
    rpm2 = (60 * 1000000) / (currentTime2 - oldTime2);
    Serial.print("   RPM 2: ");
    Serial.print(rpm2);
    oldTime2 = currentTime2;
  }

  oldDetect2 = detect2;
    Serial.print("   Ratio: ");
    if (rpm2 == 0) {
      ratio = 0;
    } else {
      ratio = rpm1 / rpm2;
    }
    Serial.print(ratio);
//    Serial.println();

}
