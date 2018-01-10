#define tempSensorPIN A0

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
  float tempC = map(temperatureRaw,0,1024,-50,300);//find out range
  Serial.print("\tCELSIUS: ");
  Serial.print(tempC);
  Serial.print("*C \t"); 
  //converts celsius into fahrenheit
  float tempF = (tempC * 9 / 5) + 32;
  Serial.print("FAHRENHEIT: ");
  Serial.print(tempF);
  Serial.println("*F");
}

