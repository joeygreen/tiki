#include <Servo.h>

Servo tikiMouthServo;
int opened = 75;
int closed = 0;
int mouthState = closed;
int warChants = 5;

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
  chant(2);
  delay(250);
  chant(2);
  delay(250);
  chant(6);
}

void chant(int itterations) {
  for (int i = 0; i < itterations; i++) {
    logMouthState(mouthState);
    tikiMouthServo.write(mouthState);
    mouthState = toggleMouth(mouthState, opened, closed);  
    delay(130);
  }
}

static int toggleMouth(int currentAngle, int opened, int closed) {
  return (currentAngle == closed) 
    ? opened 
    : closed;
}

static void logMouthState(int mouthState) {
  Serial.print("Mouth State: ");
  Serial.print(mouthState == 0 ? "Closed" : "Opened");
  Serial.print("\n");
}