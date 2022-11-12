#include <Arduino.h>
#include <confs.h>
#include <PID.h>
#include <line_array.h>
#include <state_machine.h>

LineArray lineArray(34,35,32,19,23);
state_machine sm;
RobotState robotState;
PID pid(2.1,0,1.1);
int previous_pos = 0;



void setup() {
  // put your setup code here, to run once:
  lineArray.init();
  sm.transition();
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  robotState = sm.getCurrentState();
  switch (robotState)
  {
  case RobotState::line_following:
  {
    line_position = lineArray.readValue();
    if (line_position >= 10) {
      sm.transition();
      break;
    }
    double pidOut = pid.Calculate(line_position, millis());
    Serial.println(lineArray.readValue());
    driverLeft.setSpeed(constrain(MOTOR_BASE_SPEED_LEFT + pidOut, 85, 105));
    driverRight.setSpeed(constrain(MOTOR_BASE_SPEED_RIGHT - pidOut, 85, 105));
    if (line_position != previous_pos) {
      driverLeft.brake();
      driverRight.brake();
      delay(15);
    }
    previous_pos = line_position;
    break;
  }
  case RobotState::stop_and_go:
  {
    driverLeft.brake();
    driverRight.brake();
    delay(3000);
    driverLeft.setSpeed(MOTOR_BASE_SPEED_LEFT);
    driverRight.setSpeed(MOTOR_BASE_SPEED_RIGHT);
    sm.transition();
    break;
  }
  case RobotState::obstacle_avoidance:
  {
    line_position = lineArray.readValue();
    if (line_position >= 10) {
      line_position = previous_pos;
    }
    double pidOut = pid.Calculate(line_position, millis());
    Serial.println(lineArray.readValue());
    driverLeft.setSpeed(constrain(MOTOR_BASE_SPEED_LEFT + pidOut, 90, 97));
    driverRight.setSpeed(constrain(MOTOR_BASE_SPEED_RIGHT - pidOut, 90, 97));
    if (line_position != previous_pos) {
      driverLeft.brake();
      driverRight.brake();
      delay(15);
    }
    previous_pos = line_position;
    break;
  }
  
  /*default:
    driverLeft.brake();
    driverRight.brake();
    break;*/
  }
}