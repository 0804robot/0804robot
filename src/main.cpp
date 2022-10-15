#include <Arduino.h>
#include <PID.h>
#include <Satima.h>
#include <state_machine.h>
#include <obstacle_detector.h>
#include <ESP32Servo.h>
#include <confs.h>
#include <line_array.h>

PID pid;
Satima driverLeft(18,19);
Satima driverRight(20,21);
state_machine sm;
Obstacle od(22,23,24,25,26,27);
RobotState robotState;
Servo frontServo;
LineArray lineArray(15,16,17,18,19);

void setup() {
  // put your setup code here, to run once:
  od.init();
  driverLeft.setSpeed(104, CLOCKWISE);
  driverRight.setSpeed(80, CLOCKWISE);
  frontServo.attach(9);
  sm.transition();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (robotState == RobotState::line_following && od.getDistance_front() < 5) {
    sm.transition();
  }
  robotState = sm.getCurrentState();
  switch (robotState)
  {
  case RobotState::obstacle_avoidance:
  if (od.getDistance_front() < 5) {
    float distance_left, distance_right;
    frontServo.write(60);
    distance_left = od.getDistance_front();
    frontServo.write(120);
    distance_right = od.getDistance_front();
    frontServo.write(90);
    if (distance_left > distance_right) {
      Drive60LeftRoutine(driverLeft, driverRight);
      Drive60RightRoutine(driverLeft, driverRight);

    }
  }else{
    line_position = lineArray.readValue();
    double pidOut = pid.Calculate(line_position, millis());
    driverLeft.setSpeed(MOTOR_BASE_SPEED_LEFT + pidOut, CLOCKWISE);
    driverRight.setSpeed(MOTOR_BASE_SPEED_RIGHT - pidOut, CLOCKWISE);

  }
    break;
  
  default:
    break;
  }
}