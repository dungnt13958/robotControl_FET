#include "propControl.h"
#include <math.h>
#include<Arduino.h>
#include "robotConfig.h"
#include "robotState.h"
float getAngleError(float dx, float dy, float currentYaw)
{
    float targetYaw = atan2(dy, dx);
    float error = targetYaw - currentYaw;
    error = atan2(sin(error), cos(error));
    return error;
}


void calcError(robotState &robot, controlSignal &signal, float goalX, float goalY)
{
    signal.dist = sqrt(pow(goalX-robot.x,2)+pow(goalY-robot.y,2));

    float radYaw = (float)robot.yaw;
    signal.angleError = getAngleError(goalX-robot.x, goalY-robot.y, radYaw);

    robot.angleAcc += KI_ANGLE * signal.angleError * signal.dt;
    robot.angleAcc = constrain(robot.angleAcc, -ANGLE_ACC_MAX, ANGLE_ACC_MAX);

    signal.omega = KP_ANGLE * signal.angleError + robot.angleAcc + KD_ANGLE * (signal.angleError - robot.prevAngleError)/signal.dt;

    robot.prevAngleError = signal.angleError;

    robot.veloAcc += KI_VEL * signal.dist * signal.dt;
    robot.veloAcc = constrain(robot.veloAcc, 0.0f, VEL_ACC_MAX);
    signal.v = KP_VEL * signal.dist + robot.veloAcc + KD_VEL * (signal.dist - robot.prevVeloError)/signal.dt;
    robot.prevVeloError = signal.dist;
    if(signal.v > V_MAX)
        {
        signal.v = V_MAX;
        }
        if(signal.v < V_MIN)
        {
        signal.v = V_MIN;
        }
}

void directionControl(controlSignal &signal)
{
    // if (omega > OMEGA_MAX) omega = OMEGA_MAX;
    // if (omega < -OMEGA_MAX) omega = -OMEGA_MAX;
    // v = constrain(v, V_MIN, V_MAX);


    // signal.v = constrain(signal.v, V_MIN, V_MAX);

    // // Giới hạn omega theo vận tốc tiến
    // float maxOmegaByV = 2.0f * (signal.v - V_MIN) / WHEEL_BASE;

    // if (signal.omega > maxOmegaByV)
    //     signal.omega = maxOmegaByV;

    // if (signal.omega < -maxOmegaByV)
    //     signal.omega = -maxOmegaByV;

    // // Giới hạn omega tổng
    // if (signal.omega > OMEGA_MAX)
    //     signal.omega = OMEGA_MAX;

    // if (signal.omega < -OMEGA_MAX)
    //     signal.omega = -OMEGA_MAX;


    // float vLeft  = signal.v - signal.omega * WHEEL_BASE / 2.0f;
    // float vRight = signal.v + signal.omega * WHEEL_BASE / 2.0f;
    // float maxV = max(fabs(vLeft), fabs(vRight));
    // if (maxV > V_MAX)
    // {
    //     float scale = V_MAX / maxV;
    //     vLeft *= scale;
    //     vRight *= scale;
    // }

    // if (fabs(vLeft) > 0 && fabs(vLeft) < V_MIN)
    //     vLeft = (vLeft > 0) ? V_MIN : -V_MIN;

    // if (fabs(vRight) > 0 && fabs(vRight) < V_MIN)
    //     vRight = (vRight > 0) ? V_MIN : -V_MIN;
    // float omegaLeft  = vLeft/WHEEL_RADIUS;
    // float omegaRight = vRight/WHEEL_RADIUS;
    // signal.pwmLeft  = (int)(fabs(omegaLeft)  * D_PWM_LEFT);
    // signal.pwmRight = (int)(fabs(omegaRight) * D_PWM_LEFT);

    //  ===================== THUẬT TOÁN AI =======================
    // float maxV = max(fabs(vLeft), fabs(vRight));

    // if (maxV > V_MAX)
    // {
    //     float scale = V_MAX / maxV;
    //     vLeft *= scale;
    //     vRight *= scale;
    // }

    // float omegaLeft  = vLeft / WHEEL_RADIUS;
    // float omegaRight = vRight / WHEEL_RADIUS;

    // signal.pwmLeft  = (int)(fabs(omegaLeft)  * D_PWM_LEFT);
    // signal.pwmRight = (int)(fabs(omegaRight) * D_PWM_RIGHT);

    // if (signal.pwmLeft > 0 && signal.pwmLeft < PWM_MIN)
    // {
    //     int pwmScale = PWM_MIN/signal.pwmLeft;
    //     signal.pwmLeft*=pwmScale;
    //     signal.pwmRight*=pwmScale;
    // }

    // if (signal.pwmRight > 0 && signal.pwmRight < PWM_MIN)
    // {
    //     int pwmScale = PWM_MIN/signal.pwmRight;
    //     signal.pwmLeft*=pwmScale;
    //     signal.pwmRight*=pwmScale;
    // }

    //================ Thuật toán AI 2 ===============
    // signal.v = constrain(signal.v, V_MIN, V_MAX);

    // float maxOmegaByV = 2.0f * (signal.v - V_MIN) / WHEEL_BASE;

    // if (signal.omega > maxOmegaByV)
    //     signal.omega = maxOmegaByV;

    // if (signal.omega < -maxOmegaByV)
    //     signal.omega = -maxOmegaByV;

    // if (signal.omega > OMEGA_MAX)
    //     signal.omega = OMEGA_MAX;

    // if (signal.omega < -OMEGA_MAX)
    //     signal.omega = -OMEGA_MAX;
    // float vLeft  = signal.v - signal.omega * WHEEL_BASE / 2.0f;
    // float vRight = signal.v + signal.omega * WHEEL_BASE / 2.0f;
    // float omegaLeft  = vLeft/WHEEL_RADIUS;
    // float omegaRight = vRight/WHEEL_RADIUS;
    // Serial.print("vLeft: "); Serial.print(vLeft); Serial.print(", vRight: "); Serial.print(vRight); Serial.print("omegaLeft: "); Serial.print(omegaLeft); Serial.print(", omegaRight: "); Serial.println(omegaRight);
    // signal.pwmLeft  = (int)(fabs(omegaLeft)  * D_PWM_LEFT);
    // signal.pwmRight = (int)(fabs(omegaRight) * D_PWM_RIGHT);
    // if (signal.pwmLeft > 0 && signal.pwmLeft < PWM_MIN)
    // {
    //     float scale = PWM_MIN / signal.pwmLeft;
    //     signal.pwmLeft  *= scale;
    //     signal.pwmRight *= scale;
    // }

    // if (signal.pwmRight > 0 && signal.pwmRight < PWM_MIN)
    // {
    //     float scale = PWM_MIN / signal.pwmRight;
    //     signal.pwmLeft  *= scale;
    //     signal.pwmRight *= scale;
    // }

    // ==================================== THUẬT TOÁN AI 3 ===============================
    // signal.v = constrain(signal.v, V_MIN, V_MAX);

    // Tính vận tốc hai bánh
    float vLeft  = signal.v - signal.omega * WHEEL_BASE / 2.0f;
    float vRight = signal.v + signal.omega * WHEEL_BASE / 2.0f;
    // Đổi sang vận tốc góc bánh
    float omegaLeft  = vLeft  / WHEEL_RADIUS;
    float omegaRight = vRight / WHEEL_RADIUS;

    // Serial.print("vLeft: ");
    // Serial.print(vLeft);
    // Serial.print(", vRight: ");
    // Serial.print(vRight);
    // Serial.print(", omegaLeft: ");
    // Serial.print(omegaLeft);
    // Serial.print(", omegaRight: ");
    // Serial.println(omegaRight);

    // Đổi sang PWM
    signal.pwmLeft  = (int)(fabs(omegaLeft)  * D_PWM_LEFT);
    signal.pwmRight = (int)(fabs(omegaRight) * D_PWM_RIGHT);

    // Nếu một bánh có PWM dưới PWM_MIN,
    // scale cả hai bánh cùng tỷ lệ để giữ nguyên tỷ lệ tốc độ
    float minPWM = min(signal.pwmLeft, signal.pwmRight);
    Serial.println(minPWM);
    if (minPWM > 0 && minPWM < PWM_MIN)
    {
        float scale = PWM_MIN / minPWM;
        signal.pwmLeft  *= scale;
        signal.pwmRight *= scale;
    }
    float maxPWM = max(signal.pwmLeft, signal.pwmRight);
    if (maxPWM > PWM_MAX)
    {
        float scale = PWM_MAX / maxPWM;
        signal.pwmLeft  *= scale;
        signal.pwmRight *= scale;
    }
    // Serial.println("pwmLeft: " + String(signal.pwmLeft) + ", pwmRight: " + String(signal.pwmRight));
}