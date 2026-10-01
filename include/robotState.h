#ifndef _ROBOT_STATE_H
#define _ROBOT_STATE_H
struct robotState
{
    float x = 0.0f;
    float y = 0.0f;
    float yaw = 0.0f;
    float prevAngleError = 0.0f;
    float prevVeloError = 0.0f;
    float angleAcc = 0.0f;
    float veloAcc = 0.0f;
    // long prevLeftPulse = 0, prevRightPulse = 0;
};

struct controlSignal
{
    float dt = 0.0f;
    float v = 0.0f;
    float omega = 0.0f;
    float dist = 0.0f;
    float angleError = 0.0f;
    int pwmLeft = 0;
    int pwmRight = 0;
};
#endif
