#ifndef _ROBOT_CONFIG_H
#define _ROBOT_CONFIG_H

// Robot geometry
constexpr float WHEEL_DIAMETER = 6.50f;   // cm
constexpr float WHEEL_RADIUS   = 3.25f;   // cm
constexpr float WHEEL_BASE     = 17.2f;  // cm

// Encoder
constexpr float ENCODER_PPR = 374.0f;

// Control gains
constexpr float KP_ANGLE    = 2.60f;
constexpr float KP_VEL      = 3.00f;
constexpr float KI_VEL      = 0.05f;
constexpr float KI_ANGLE    = 0.02f;
constexpr float KD_VEL      = 0.07f;
constexpr float KD_ANGLE    = 0.2f;
constexpr float ANGLE_ACC_MAX = 0.5f;
constexpr float VEL_ACC_MAX = 7.0f;
constexpr float ANGLE_DEADBAND = 2.0f * M_PI / 180.0f;
constexpr float D_PWM_LEFT = 4.384f;
constexpr float D_PWM_RIGHT = 4.637f;

#endif