/*
 * Krystal Bernal
 * CSULA Baja SAE
 * 
 * This code uses a hall effect sensor and revolving magnet as a tachometer for 
 * reading rpm of drive and driven on a CVT. Ratio is used for tuning. 
 * 
 * Previous code used built-in Arduino interrupt, but was unreliable. According to Arduino's
 * documentation: "millis() relies on interrupts to count, so it will never increment inside an ISR.
 * micros() works initially, but will start behaving erratically after 1-2 ms."
 */

//max fan rpm = 4000

#define HE_Pin A0

unsigned long currentTime = 0;
unsigned long oldTime = 0;

bool detect = false;
bool oldDetect = false;

void setup() {
  Serial.begin(9600);
  pinMode(HE_Pin, INPUT_PULLUP);
}

void loop() {
  int HE_Raw = analogRead(HE_Pin);
  
  //update these values dynamically
  if (HE_Raw > 750) {
    detect = true;
  } else {
    detect = false;
  }
  if ((detect != oldDetect) && detect) {
    currentTime = micros();
    Serial.print("RPM: ");
    Serial.println((60*1000000)/(currentTime - oldTime));
    oldTime = currentTime;
  }
  oldDetect = detect;
}
