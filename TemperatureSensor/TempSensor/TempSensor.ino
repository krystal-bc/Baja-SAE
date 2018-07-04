#define tempSensorPIN A14

void setup() {
  Serial.begin(9600);
  pinMode(tempSensorPIN, INPUT);
}

void loop() {
  readTemp();
  delay(50);
}

void readTemp() {
  float temperatureRaw = analogRead(tempSensorPIN);
  Serial.print("RAW: ");
  Serial.print(temperatureRaw);
  //converts raw data into degrees celsius
  float tempF = map(temperatureRaw,0,255,-50,300);//find out range
  Serial.print("\tFAHRENHEIT: ");
  Serial.print(tempF);
  Serial.print("*F \t"); 
  //converts celsius into fahrenheit
  float tempC = (tempF * 5 / 9) - 32;
  Serial.print("CELSIUS: ");
  Serial.print(tempC);
  Serial.println("*C");
}

