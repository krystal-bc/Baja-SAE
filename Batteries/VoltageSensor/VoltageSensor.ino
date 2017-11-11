/* Krystal Bernal
 * Last Updated: 11/10/17
 * 
 * This program reads battery voltage from a voltage sensor and lights up an LED if the battery is too low
 * 
*/
#define LEDlowBattery 8
#define voltageSensor A1

void setup() {
  pinMode(voltageSensor, INPUT);
  pinMode(LEDlowBattery, OUTPUT);
  digitalWrite(LEDlowBattery, LOW);
  Serial.begin(9600);
}
void loop() {
  checkVoltage();
  delay(500);
}

void checkVoltage(){
  float batteryLimit = 10;
  int voltageRaw = analogRead(voltageSensor);
  //values of the onboard resistors
  float R1 = 30000.0;
  float R2 = 7500.0;
  //5:1 converstion ratio
  float vOut = (voltageRaw * 5.0) / 1024.0;
  float vIn = vOut / (R2 / (R1 + R2));

  Serial.print("Voltage: ");
  Serial.println(vIn, 2);
  
  if (vIn < batteryLimit){
    digitalWrite(LEDlowBattery, HIGH);
  }else{
    digitalWrite(LEDlowBattery, LOW);
  }
}
