#define HE_Pin A0

boolean detect = false;
boolean lastDetect = false;

int currentTime = 0;
int lastTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(HE_Pin, INPUT);
}

void loop() {
  int HE_Raw = analogRead(HE_Pin);
  if(HE_Raw > 750){
    detect = true;
  }else{
    detect = false;
  }
  if(detect != lastDetect){
    Serial.println(millis());
  }
  detect = lastDetect;

}
