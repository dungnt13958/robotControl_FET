#ifndef _PROP_CONTROL_H
#define _PROP_CONTROL_H
#include <Arduino.h>
#include "robotState.h"
#define V_MAX 50.0f // cm/s
#define OMEGA_MAX 3.14f // rad/s
#define V_MIN 30.0f // cm/s
const float d = 6.2f;    // Đường kính bánh xe (cm)
const float L = 17.2f;   // Khoảng cách 2 bánh xe (cm)
const float PPR = 374.0; // Số xung/vòng của Encoder (thay đúng số thực tế)
const float K = (M_PI * d) / PPR; // Quãng đường trên 1 xung (cm/xung)
const float PWM_MIN = 40.0f;
const float PWM_MAX = 83.0f;
const unsigned long goalPulse = 3840;



float poseError(float x, float y, float goalX, float goalY);

float getAngleError(float dx, float dy, float radYaw);

void directionControl(controlSignal &signal);

void calcError(robotState &robot, controlSignal &signal, float goalX, float goalY);

#endif