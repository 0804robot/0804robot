#include <Arduino.h>
#include <confs.h>
#include <PID.h>
#include <line_array.h>
#include <state_machine.h>
#include <FCH.h>

LineArray lineArray(34,35,32,19,23);
state_machine sm;
RobotState robotState;
PID pid(17,0,0);
FCH driverLeft(5);
FCH driverRight(6);



void setup() {
  // put your setup code here, to run once:
  lineArray.init();
  sm.transition();
  driverLeft.setSpeed(MOTOR_BASE_SPEED_LEFT);
  driverRight.setSpeed(180 - MOTOR_BASE_SPEED_RIGHT);
}

void loop() {
  // put your main code here, to run repeatedly:
  robotState = sm.getCurrentState();
  switch (robotState)
  {
  case RobotState::line_following:
    line_position = lineArray.readValue();
    double pidOut = pid.Calculate(line_position, millis());
    driverLeft.setSpeed(MOTOR_BASE_SPEED_LEFT + pidOut);
    driverRight.setSpeed(180 - MOTOR_BASE_SPEED_RIGHT - pidOut);
    break;
  
  default:
    break;
  }
}