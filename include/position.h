#ifndef _POSITION_H
#define _POSITION_H
#include <Arduino.h>

class position
{
private:
    float xR = 0.0f;
    float yR = 0.0f;
    float headR = 0.0f;

    bool receiving = false;
    byte index = 0;
    bool uartRead = false;
public:
    int serialRead(HardwareSerial &Serial, char* buffer, size_t buffersize);
    void getRobotPose(float &x, float &y, float &heading);
    
};
#endif