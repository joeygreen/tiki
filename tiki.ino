#include <Servo.h>

Servo tikiMouthServo;
enum mouthState { 
  Opened = 75, 
  Closed = 0 
};
mouthState currentMouthState = Closed;
int warChants = 4;

void setup() {
  tikiMouthServo.attach(9);
  
  Serial.begin(9600);
}

void loop() {  
  for(int i = 0; i < warChants; i++) {
    warChant();
    delay(275);
  }
  exit(0);  
}

void warChant() {
  chant(2, 130); // ooh
  delay(250);
  chant(2, 130); // ahh
  delay(250);
  chant(6, 130); // aye ooh ooh ha
}

void chant(int itterations, int delayMs) {
  for (int i = 0; i < itterations; i++) {
    logMouthState(currentMouthState);
    tikiMouthServo.write(currentMouthState);
    currentMouthState = toggleMouth();  
    delay(delayMs);
  }
}

mouthState toggleMouth() {
  return currentMouthState == Closed ? Opened : Closed;
}

static void logMouthState(mouthState state) {
  Serial.print("Mouth State: ");
  Serial.print(state == Closed ? "Mouth Closed" : "Mouth Opened");
  Serial.print("\n");
}