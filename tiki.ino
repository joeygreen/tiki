#include <Servo.h>

enum servoState { 
  Opened = 75, 
  Closed = 0
};

Servo testServo;

class AnimatronicServo {
  private: Servo servo;
  private: byte pin;
    
  private: servoState state;
  public: servoState getState() {
    return state;
  }

  public:
    AnimatronicServo(Servo servo, byte pin, servoState state) {
      this->servo = servo;
      this->pin = pin;
      this->state = state;
      init();
    }

  private:
    init() {
      servo.attach(pin);
      servo.write(state);
    }

  public:
    void toggleState() {
      if (state == Closed) {
        open();
      } else {
        close();        
      }
    }

  public: void open() {
    state = Opened;
    servo.write(state);    
  }

  public: void close() {
    state = Closed;
    servo.write(state);
  }

};

// servos
AnimatronicServo mouthServo = AnimatronicServo(testServo, 13, Closed);

// show constants
const int warChants = 4;

void setup() {
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
  toggleOpenedClosedState(mouthServo, 2, 130); // ooh
  delay(250);
  toggleOpenedClosedState(mouthServo, 2, 130); // ahh
  delay(250);
  toggleOpenedClosedState(mouthServo, 6, 130); // aye ooh ooh ha
}

static void toggleOpenedClosedState(AnimatronicServo animatronicServo, int itterations, int delayMs) {
  logServoState(animatronicServo.getState());
  for (int i = 0; i < itterations; i++) {
    animatronicServo.toggleState();
    logServoState(animatronicServo.getState());
    delay(delayMs);
  }
}

static void logServoState(servoState state) {
  Serial.print("Servo State: ");
  Serial.print(state);
  Serial.print("\n");
}