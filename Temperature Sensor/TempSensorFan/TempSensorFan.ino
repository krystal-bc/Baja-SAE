/* Krystal Bernal
   Last updated: 11/10/17

   This program reads temperature from an LM35 temperature sensor and uses it to control the speed of a CPU cooling fan
*/

#define tempSensorPIN A2
#define fanPIN 3



void setup() {
  Serial.begin(9600);
  pinMode(fanPIN, OUTPUT);
}

void loop() {
  writeFan(readTemp());
  delay(1000);
}

float readTemp() {
  float temperature = analogRead(tempSensorPIN);
  //converts raw data into degrees celsius and prints it out: 500mV/1024
  //temperature = map(x,0,1024,-55.0,150.0); //this might work better
  temperature = temperature * (500 / 1024);
  Serial.print("CELSIUS: ");
  Serial.print(temperature);
  Serial.println("*C ");
  //converts celsius into fahrenheit
  temperature = (temperature * 9 / 5) + 32;
  Serial.print("FAHRENHEIT: ");
  Serial.print(temperature);
  Serial.println("*F");
  return temperature;
}

void writeFan(float temperature) {
  int fanSpeed = map(temperature, 80, 302, 0, 255); //change this to proper range
  analogWrite(fanPIN, fanSpeed);
}
