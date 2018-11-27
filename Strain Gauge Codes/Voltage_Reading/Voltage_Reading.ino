/*
  ReadAnalogVoltage

  Reads an analog input on pin A0 and A1, converts it to voltage, and prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/ReadAnalogVoltage

      The values used for the wheatstone bridge in this case are:
      R1: 330 Ohm
      R2: 470 Ohm
      R3: SG at 350 +/-.1 Ohm
      R4: 470 Ohm
      Since the bridge is unbalanced due to R1 != R3, the output voltage is off set about 0.08V or 80mV
      After testing using human strength, the following values were attained:
      MAX: +0.0
      MIN: -0.0 
*/


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:

  
  // Convert the analog reading (which goes from 0 - 350) to a voltage (0 - 5V):
//Value added to acount for an initially inbalanced bridge
  double voltageAve = 0;
  int count = 0;
  unsigned long tim = millis();
  int timecounter;
  
  
  while((millis()-tim) < 30000){
    double sensorValue1 = analogRead(A0);
    double sensorValue2 = analogRead(A1);
    double voltage1 = ((sensorValue1) * 5.0 )/ 1023.0;
    double voltage2 = ((sensorValue2) * 5.0 )/ 1023.0;
    double voltageDiff = (voltage1 - voltage2);  
    voltageAve=(voltageDiff+count*voltageAve)/(count+1);
    count=count+1;  
  }
  if (tim > 30000){
    timcounter += 1;
    tim *= timecounter;
  }
  
  // print out the value you read:
  /*Serial.print("Time Elapsed: ");
  Serial.print(millis());
  Serial.print("ms  ");*/
  Serial.print(voltageAve, 20); //floating point set to 8 decimal points, possible to reduce, inittially at 10
  Serial.println(" V");
  
}
