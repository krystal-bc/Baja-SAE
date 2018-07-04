/* Krystal Bernal
   Last updated: 1/24/18
   Tracks when/how many times a button is pushed
*/

#define button1 A6

unsigned int btnState1;
unsigned int lastBtnState1;
unsigned int btnCounter1 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(button1, INPUT_PULLUP);

}

void loop() {
  readButtons();
  
}

void readButtons(){
  int btn1 = analogRead(button1);
  //int btn2 = analogRead(button2);
  if(btn1 < 1000){
    btnState1 = 1;//off
  }else{
    btnState1 = 0;//on
  }

  if(btnState1 != lastBtnState1){
    if(btnState1 == 0){
      btnCounter1++;
      Serial.print("button 1 pressed: ");
      Serial.println(btnCounter1);
      //reset button counter
    }
    delay(50);
  }
  lastBtnState1 = btnState1;
}
