/* Krystal Bernal
 *  Last updated: 11/11/17
 *  
 *  This program sweeps a 12V CPU cooling fan
 * 
*/

#define fanPIN 4

void setup() {
  Serial.begin(9600);
  pinMode(fanPIN, OUTPUT);
  analogWrite(fanPIN, 0);

}

void loop() {
  for(int i = 0; i<256; i++){
    Serial.println(i);
    analogWrite(fanPIN, i);
    delay(50);
  }
  delay(3000);
  for(int i = 256; i>0; i--){
    Serial.println(i);
    analogWrite(fanPIN, i);
    delay(50);
  }
  delay(3000);
}
