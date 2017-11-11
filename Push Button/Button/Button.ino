/*  Krystal Bernal
 *  Last updated: 11/1/17
 *  
 *  This button reads the pressing of a push button
 * 
*/

#define BUTTON_PIN 8

int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  readBtn();
}

void readBtn() {
  buttonState = digitalRead(BUTTON_PIN);
  if (buttonState != lastButtonState) {
    if (buttonState == LOW) {
      // if the current state is LOW then the button went from unpushed to pushed:
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);
    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state
  lastButtonState = buttonState;
}
