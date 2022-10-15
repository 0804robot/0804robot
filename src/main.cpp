#include <Arduino.h>
#include <PID.h>
#include <FCH.h>
#include <state_machine.h>
#include <obstacle_detector.h>
#include <confs.h>
#include <line_array.h>

#if defined(ESP32) 
  #include <ESP32Servo.h>
#else 
  #include <Servo.h>
#endif

PID pid;
FCH driverLeft(5);
FCH driverRight(6);
state_machine sm;
Obstacle od(8,9,8,9,8,9);
RobotState robotState;
Servo frontServo;
LineArray lineArray(3,18,19, 20, 21);

void setup() {
  // put your setup code here, to run once:
  od.init();
  driverLeft.setSpeed(104);
  driverRight.setSpeed(80);
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
    driverLeft.setSpeed(MOTOR_BASE_SPEED_LEFT + pidOut);
    driverRight.setSpeed(MOTOR_BASE_SPEED_RIGHT - pidOut);

  }
    break;
  
  default:
    break;
  }
}