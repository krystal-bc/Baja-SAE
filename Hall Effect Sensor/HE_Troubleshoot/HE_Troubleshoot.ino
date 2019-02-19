#define HE_Pin1 A4

unsigned long currentTime1 = 0;
unsigned long oldTime1 = 0;

bool detect1 = false;
bool oldDetect1 = false;

int rpm1 = 0;

int HE_Raw1;

void setup() {
  Serial.begin(9600);
  pinMode(HE_Pin1, INPUT);
}

void loop() {
  HE_Raw1 = analogRead(HE_Pin1);
  //printRaw();
  printRPM();
}

void printRaw() {
  
  Serial.println(HE_Raw1);
}

void printRPM() {
  if (HE_Raw1 < 325) {
    detect1 = true;
  } else {
    detect1 = false;
  }
  if ((detect1 != oldDetect1) && detect1) {
    currentTime1 = micros();
    rpm1 = (60 * 1000000) / (currentTime1 - oldTime1);
    Serial.print("RPM 1: ");
    Serial.println(rpm1);
    oldTime1 = currentTime1;
  }

  oldDetect1 = detect1;
}
