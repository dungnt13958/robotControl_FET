#include <Arduino.h>
#include <Wire.h>
#include<math.h>
#include "propControl.h"
#include "motorControl.h"
#include "position.h"
#include "robotConfig.h"
#include "robotState.h"

controlSignal signal;
robotState robot;
position robotPose;
unsigned long lastTime = 0;
int i = 0;
int pwm = 60;
const float goal[2] = {420.0f, 60.0f};
// const float goal[2] = {0.0f, 15.0f};
void setup() 
{
  initSetup();
  lastTime = millis();

}
char buffer[50];

void loop() 
{
  // allForward(180, 180);
  unsigned long now = millis();
  signal.dt = (now - lastTime)/1000.0f;
  lastTime = now;
  signal.dt = max(signal.dt, 0.001f);
  int fd = 0;
  while (fd <= 0)
  {
    fd = robotPose.serialRead(Serial3, buffer, sizeof(buffer));
  }
  robotPose.getRobotPose(robot.x, robot.y, robot.yaw);
  calcError(robot, signal, goal[i], goal[i+1]);
  if (fabs(signal.angleError) < ANGLE_DEADBAND)
  {
      signal.omega = 0.0f;
  }
  directionControl(signal);
  if(signal.dist < 5.0f)
  {
    i+= 2;
    robot.angleAcc = 0.0f;
    robot.veloAcc = 0.0f;
    robot.prevAngleError = 0.0f;
    robot.prevVeloError = 0.0f;
    if(i > 1)
    {
      signal.pwmLeft = 0;
      signal.pwmRight = 0;
      robot.angleAcc = 0;
      robot.veloAcc = 0;
      robot.prevAngleError = 0;
      robot.prevVeloError = 0;
      allForward(signal.pwmLeft, signal.pwmRight);
      while(1) stop(); // freeze
    }
  }
  allForward(signal.pwmLeft, signal.pwmRight);
}
