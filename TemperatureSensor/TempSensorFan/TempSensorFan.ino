/* Krystal Bernal
   Last updated: 11/10/17
   This program reads temperature from an LM34 temperature sensor and uses it to control a CPU cooling fan
*/

#define tempSensorPIN A2
#define fanPIN 3

void setup() {
  Serial.begin(9600);
  pinMode(fanPIN, OUTPUT);
}

void loop() {
  monitorTemp();
}

void monitorTemp() {
  float temperatureRaw = analogRead(tempSensorPIN);
  Serial.print("RAW: ");
  Serial.print(temperatureRaw);
  //converts raw data into degrees celsius
  float tempC = map(temperatureRaw,0,1024,-50,300);//find out range
  Serial.print("\tCELSIUS: ");
  Serial.print(tempC);
  Serial.print("*C \t"); 
  //converts celsius into fahrenheit
  float tempF = (tempC * 9 / 5) + 32;
  Serial.print("FAHRENHEIT: ");
  Serial.print(tempF);
  Serial.println("*F");

  if (tempF > 80){
   digitalWrite(fanPin, HIGH); 
  }
}
