#include <Arduino.h>
#include <confs.h>
#include <PID.h>
#include <line_array.h>
#include <state_machine.h>

LineArray lineArray(34,35,32,19,23);
state_machine sm;
RobotState robotState;
PID pid(1.2,0,1.1);
int previous_pos = 0;



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
    driverLeft.setSpeed(constrain(MOTOR_BASE_SPEED_LEFT + pidOut, 90, 98));
    driverRight.setSpeed(constrain(MOTOR_BASE_SPEED_RIGHT - pidOut, 90, 98));
     if (line_position != previous_pos) {
        driverLeft.brake();
        driverRight.brake();
        delay(15);
      }
      previous_pos = line_position;
    break;
  
  default:
     break;
  }
}