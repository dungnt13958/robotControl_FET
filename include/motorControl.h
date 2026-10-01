#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>

const byte IN1 = 7;
const byte IN2 = 6;
const byte IN3 = 5;
const byte IN4 = 4;

const byte ENA = 11;
const byte ENB = 12;
const byte leftEncoderA = 18, leftEncoderB = 19;
const byte rightEncoderA = 2, rightEncoderB = 3;
// Liên kết các biến tốc độ toàn cục từ file main
extern int pwmL, pwmR;
extern int iniPwm;

// Khai báo các hàm điều khiển hướng
void stop();
void forward();
void backWard();
void turnLeft();
void turnRight();
void allForward(float pwmLeft, float pwmRight);
void initSetup();
#endif