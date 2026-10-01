#include "motorControl.h"
volatile long leftPulseCount = 0, rightPulseCount = 0;
void countPulseLeft() 
{
  if  (digitalRead(leftEncoderB) == HIGH) leftPulseCount++;
  else leftPulseCount--;
}

void countPulseRight() 
{
  if (digitalRead(rightEncoderB) == LOW) rightPulseCount++;
  else rightPulseCount--;
}

void stop() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
    delay(100);
}

void allForward(float pwmLeft, float pwmRight)
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, pwmLeft);
    analogWrite(ENB, pwmRight);
}

void turnLeft() {
    stop();
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, iniPwm/2);
    analogWrite(ENB, iniPwm/2);
}

void turnRight() {
    stop();
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA, iniPwm/2);
    analogWrite(ENB, iniPwm/2);
}

void backward() {
    stop();
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA, iniPwm);
    analogWrite(ENB, iniPwm);
}

void initSetup()
{
Serial.begin(115200);
  Serial3.begin(115200);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(leftEncoderA, INPUT_PULLUP);
  pinMode(leftEncoderB, INPUT_PULLUP);
  pinMode(rightEncoderA, INPUT_PULLUP);
  pinMode(rightEncoderB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(leftEncoderA), countPulseLeft, RISING);
  attachInterrupt(digitalPinToInterrupt(rightEncoderA), countPulseRight, RISING);
}