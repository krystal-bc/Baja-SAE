#define voltageSensor A1;
int voltageRaw = 0;

void setup() {
  pinMode(analogInput, INPUT);
  Serial.begin(9600);
}
void loop() {
  voltageRaw = analogRead(voltageSensor);
  float R1 = 30000.0;
  float R2 = 7500.0;
  float vOut = (voltageRaw * 5.0) / 1024.0;
  float vIn = vOut / (R2 / (R1 + R2));

  Serial.print("Voltage: ");
  Serial.println(vIn, 2);
  delay(500);
}
