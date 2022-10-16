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

PID pid(5,0,0);
FCH driverLeft(2);
FCH driverRight(16);
state_machine sm;
//Obstacle od(26,13,8,9,8,9);
RobotState robotState;
Servo frontServo;
LineArray lineArray(34,35,32,19,23);

void setup() {
  // put your setup code here, to run once:
  //od.init();
  driverLeft.setSpeed(104);
  driverRight.setSpeed(80);
  frontServo.attach(9);
  lineArray.init();
  sm.transition();
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  line_position = lineArray.readValue();
  Serial.print("pos ");
  Serial.println(line_position);
  double pidOut = pid.Calculate(line_position, millis());
  driverLeft.setSpeed(180 - MOTOR_BASE_SPEED_LEFT + pidOut);
  driverRight.setSpeed(MOTOR_BASE_SPEED_RIGHT - pidOut);
  Serial.print("left");
  Serial.println(MOTOR_BASE_SPEED_LEFT + pidOut);
  Serial.print("right");
  Serial.println(180 - MOTOR_BASE_SPEED_LEFT - pidOut);
  Serial.print("PID ");
  Serial.println(pidOut);
  //delay(60);
  //driverLeft.brake();
  //driverRight.brake();
  delay(10);
  // put your main code here, to run repeatedly:
  /*if (robotState == RobotState::line_following && od.getDistance_front() < 5) {
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
    line_position = lineArray.readValue();
    double pidOut = pid.Calculate(line_position, millis());
    driverLeft.setSpeed(MOTOR_BASE_SPEED_LEFT + pidOut);
    driverRight.setSpeed(MOTOR_BASE_SPEED_RIGHT - pidOut);
    break;
  }*/
}