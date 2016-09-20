#include "Servo.h"
#define servoPin 9

Servo servoMotor;
//HC-SR04 Ping distance sensor pins
#define trigPin 7
#define echoPin 8


//Motor pins
#define rightPWM 12
#define rightPos 5
#define rightNeg 6
#define leftPWM 11
#define leftPos 3
#define leftNeg 4
long duration, distance;


void motorForward() {

  digitalWrite(leftPos, HIGH);
  digitalWrite(rightPos, HIGH);
  digitalWrite(leftNeg, LOW);
  digitalWrite(rightNeg, LOW);
}

void motorReverse() {
  digitalWrite(leftPos, LOW);
  digitalWrite(rightPos, LOW);
  digitalWrite(leftNeg, HIGH);
  digitalWrite(rightNeg, HIGH);
}

void motorStop() {
  digitalWrite(rightPos, LOW);
  digitalWrite(rightNeg, LOW);
  digitalWrite(leftPos, LOW);
  digitalWrite(leftNeg, LOW);
}
void motorRight() {
  digitalWrite(leftPos, LOW);
  digitalWrite(rightPos, LOW);
  digitalWrite(leftNeg, HIGH);
  digitalWrite(rightNeg, LOW);
}

void setup() {
  Serial.begin (9600);
  analogWrite(rightPWM, 255);
  analogWrite(leftPWM, 255);

  servoMotor.attach(servoPin);
  analogWrite(rightPWM, 255);
  analogWrite(leftPWM, 255);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(rightNeg, OUTPUT);
  pinMode(rightPos, OUTPUT);
  pinMode(leftNeg, OUTPUT);
  pinMode(leftPos, OUTPUT);

  motorStop();
  delay(5000);

}
void ping() {

  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
}
void loop() {

  ping();
  servoMotor.write(0); // Rotate Servo to 0 Degrees
  delay(15); // Delay to allow Servo time to Move
  ping();
  servoMotor.write(180); // Rotate Servo to 0 Degrees
  delay(15); // Delay to allow Servo time to Move
  ping();
  servoMotor.write(90); // Rotate Servo to 0 Degrees
  delay(15); // Delay to allow Servo time to Move
  ping();
  if (distance >= 150 || distance <= -1) {
    Serial.println("Out of range");
  }
  if ( distance <= 35) {
    Serial.println("Stop");
    motorStop();
    delay(1000);
    Serial.println("Reverse");
    motorReverse();
    delay(500);
    Serial.println("Right Turn");
    motorRight();
    delay(750);
  }
  if (distance >= 36) {
    Serial.println(distance);
    motorForward();

  }

  delay(50);
}
