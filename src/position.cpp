#include "position.h"
#include <Arduino.h>
#include <math.h>

int position::serialRead(HardwareSerial &serial, char buffer[], size_t bufferSize) 
{
    int processResult = 0;
    bool newPacket = false;
    while(serial.available())
    {
        char c = serial.read();
        if (c == '<')
        {
            receiving = true;
            index = 0;
        }
        else if (c == '>' && receiving)
        {
            buffer[index] = '\0'; // Null-terminate the string
            Serial.println(buffer);
            index = 0; // Reset index for next message
            newPacket = true;
            receiving = false;
        } 
        else if (receiving)
        {
            if(index < bufferSize - 1)
            {
                buffer[index++] = c; // Store character in buffer
            }
            else
            {
                receiving = false;
                index = 0;
            }
        }
    }
    if (newPacket)
    {
        char* p1 = strchr(buffer, '|');
        char* p2 = p1 ? strchr(p1 + 1, '|') : nullptr;
        if (p1 && p2)
        {
            *p1 = '\0';
            *p2 = '\0';
            xR = atof(buffer);
            yR = atof(p1 + 1);
            headR = atof(p2 + 1);
            uartRead = true;
            processResult = 1;
        }
    }
    return processResult;
}

void position::getRobotPose(float &x, float &y, float &heading)
{
    if(uartRead)
    {
        uartRead = false;
        x = xR;
        y = yR;
        heading = headR;
    }
}