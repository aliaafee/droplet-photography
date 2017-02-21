#include <Servo.h>

#define GATE_OPEN 1
#define GATE_CLOSED 0

Servo gateServo;

volatile int gateState;

const int servoPin = 9;
const int buttonPin = 2;
const int flashPin = 13;
const int cameraPin = 12;

void openGate() {
  gateServo.write(0);
}

void closeGate() {
  gateServo.write(90);
}


void onButtonPress() {
  gateState = GATE_OPEN;
}


void setup() {
  gateServo.attach(servoPin);
  pinMode(buttonPin, INPUT);
  pinMode(flashPin, OUTPUT);
  pinMode(cameraPin, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(2), onButtonPress, CHANGE);
  
  closeGate();
  gateState = GATE_CLOSED;
  
}

void loop() {
  if (gateState == GATE_OPEN) {
    digitalWrite(cameraPin, HIGH);
    delay(1000);
    openGate();
    //delay(1000);
    //closeGate();
    //delay(1000);
    gateState = GATE_CLOSED;
  }

  int value;
  value = analogRead(0);
  if (value >500) {
    delay(150);
    digitalWrite(flashPin, HIGH);
    delay(1000);
    digitalWrite(flashPin, LOW);
    digitalWrite(cameraPin, LOW);
    delay(000);
    closeGate();
  }
}
