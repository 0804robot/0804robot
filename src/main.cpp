#include <Arduino.h>
#include <confs.h>
#include <PID.h>
#include <line_array.h>
#include <state_machine.h>
#include <Satima.h>

LineArray lineArray(15,16,17,18,19);
state_machine sm;
RobotState robotState;
PID pid(1,0,0);
Satima driverLeft(5,6);
Satima driverRight(5,6);



void setup() {
  // put your setup code here, to run once:
  lineArray.init();
  driverLeft.setMaxSpeed(255);
  driverRight.setMaxSpeed(255);
  sm.transition();
  driverLeft.setSpeed(MOTOR_BASE_SPEED, CLOCKWISE);
  driverRight.setSpeed(MOTOR_BASE_SPEED, CLOCKWISE);
}

void loop() {
  // put your main code here, to run repeatedly:
  robotState = sm.getCurrentState();
  switch (robotState)
  {
  case RobotState::line_following:
    line_position = lineArray.readValue();
    double pidOut = pid.Calculate(line_position, millis());
    driverLeft.setSpeed(MOTOR_BASE_SPEED + pidOut, CLOCKWISE);
    driverRight.setSpeed(MOTOR_BASE_SPEED - pidOut, CLOCKWISE);
    break;
  
  default:
    break;
  }
}