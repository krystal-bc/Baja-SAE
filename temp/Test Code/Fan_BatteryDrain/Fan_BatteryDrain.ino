/* Krystal Bernal
 * Last Updated: 1/25/18
 * 
 * This program drains a battery with a fan, monitors battery voltage from a voltage sensor, 
 * and lights up an LED if the battery is too low
 * 
*/
#define LEDlowBattery 30
#define voltageSensor A11
int motorPin = 13;

void setup() {
  pinMode(voltageSensor, INPUT);
  pinMode(LEDlowBattery, OUTPUT);
  digitalWrite(LEDlowBattery, LOW);
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  checkVoltage();

}

void checkVoltage(){
  float batteryLimit = 9;
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
    analogWrite(motorPin, 0);
    digitalWrite(LEDlowBattery, HIGH);
  }else{
    analogWrite(motorPin, 255);
    digitalWrite(LEDlowBattery, LOW);
  }
}
