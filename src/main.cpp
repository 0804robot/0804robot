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

PID pid(1.4,0,0);
int solid_line_count = 0;

state_machine sm;
Obstacle od(26,13,17,9,33,25);
RobotState robotState;
Servo frontServo;
LineArray lineArray(34,35,32,19,23);
int previous_pos = 0;

void setup() {
  // put your setup code here, to run once:
  od.init();
  //driverLeft.setSpeed(MOTOR_BASE_SPEED_LEFT);
  //driverRight.setSpeed(MOTOR_BASE_SPEED_RIGHT);
  frontServo.attach(21);
  frontServo.write(90);
  lineArray.init();
  sm.transition();
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  /*line_position = lineArray.readValue();
  //Serial.print("pos ");
  //Serial.println(line_position);
  double pidOut = pid.Calculate(line_position, millis());
  driverLeft.setSpeed(constrain(MOTOR_BASE_SPEED_LEFT + pidOut, 90, 105));
  driverRight.setSpeed(constrain(MOTOR_BASE_SPEED_LEFT - pidOut, 90, 105));
  Serial.print("left");
  Serial.println(MOTOR_BASE_SPEED_LEFT + pidOut);
  Serial.print("right");
  Serial.println(180 - MOTOR_BASE_SPEED_LEFT - pidOut);
  Serial.print("PID ");
  Serial.println(pidOut);
  if (line_position != previous_pos) {
    driverLeft.brake();
    driverRight.brake();
    delay(15);
  }
  previous_pos = line_position;*/
  //delay(60);
  //driverLeft.brake();
  //driverRight.brake();
  //delay(10);
  // put your main code here, to run repeatedly:
  /*if (robotState == RobotState::line_following && od.getDistance_front() < 5) {
    sm.transition();
  }
  robotState = sm.getCurrentState();
  switch (robotState)
  {
  case RobotState::obstacle_avoidance:*/
  //Serial.println("front distance :");
 // Serial.println(od.getDistance_front());
 //START OF WORKING CODE
  /*if (od.getDistance_front() < 7) {
    driverLeft.brake();
    driverRight.brake();
    float distance_left, distance_right;
    frontServo.write(50);
    delay(200);
    distance_right = od.getDistance_front();
    frontServo.write(130);
    delay(200);
    distance_left = od.getDistance_front();
    frontServo.write(90);
    if (distance_left > distance_right) {
      Serial.println("right obstacle");
      Drive90LeftRoutine();
      Drive90RightRoutine();
      Drive90RightRoutine();

    }else{
      Serial.println("left obstacle");
      Drive90RightRoutine();
      Drive90LeftRoutine();
      Drive90LeftRoutine();
    }
  }else{*/
    line_position = lineArray.readValue();
    //Serial.print("pos ");
    //Serial.println(line_position);
    if (od.getDistance_front() < 10 && od.getDistance_left() < 10 && od.getDistance_right() < 10 && sm.getCurrentState() == RobotState::line_following) {
      driverLeft.brake();
      driverRight.brake();
      delay(3000);
      driverLeft.setSpeed(80);
      driverRight.setSpeed(81);
      delay(200);
      Drive90LeftRoutine();
      Drive90LeftRoutine();
      sm.transition();
    }else if (sm.getCurrentState() == RobotState::line_following){
      double pidOut = pid.Calculate(line_position, millis());
      driverLeft.setSpeed(constrain(MOTOR_BASE_SPEED_LEFT + pidOut, 90, 105));
      driverRight.setSpeed(constrain(MOTOR_BASE_SPEED_LEFT - pidOut, 90, 105));
      //Serial.print("left");
      Serial.println(MOTOR_BASE_SPEED_LEFT + pidOut);
      //Serial.print("right");
      Serial.println(180 - MOTOR_BASE_SPEED_LEFT - pidOut);
      //Serial.print("PID ");
      Serial.println(pidOut);
      if (line_position != previous_pos) {
        driverLeft.brake();
        driverRight.brake();
        delay(15);
      }
      previous_pos = line_position;
    }else if (sm.getCurrentState() == RobotState::obstacle_avoidance) {
      if (line_position == previous_pos) {
        sm.transition();
      }
      if (od.getDistance_front() < 7) {
        driverLeft.brake();
        driverRight.brake();
        float distance_left, distance_right;
        frontServo.write(50);
        delay(200);
        distance_right = od.getDistance_front();
        frontServo.write(130);
        delay(200);
        distance_left = od.getDistance_front();
        frontServo.write(90);
        if (distance_left > distance_right) {
          Serial.println("right obstacle");
          Drive90LeftRoutine();
          Drive90RightRoutine();
          Drive90RightRoutine();
        }else{
          Serial.println("left obstacle");
          Drive90RightRoutine();
          Drive90LeftRoutine();
          Drive90LeftRoutine();
        }
      }else{
        double pidOut = pid.Calculate(line_position, millis());
        driverLeft.setSpeed(constrain(MOTOR_BASE_SPEED_LEFT + pidOut, 90, 105));
        driverRight.setSpeed(constrain(MOTOR_BASE_SPEED_LEFT - pidOut, 90, 105));
        //Serial.print("left");
        Serial.println(MOTOR_BASE_SPEED_LEFT + pidOut);
        //Serial.print("right");
        Serial.println(180 - MOTOR_BASE_SPEED_LEFT - pidOut);
        //Serial.print("PID ");
        Serial.println(pidOut);
        if (line_position != previous_pos) {
          driverLeft.brake();
          driverRight.brake();
          delay(15);
        }
        previous_pos = line_position;
      }
    }
  

  //}
  //END OF WORKING CODE
  /*  break;
  
  default:
    line_position = lineArray.readValue();
    double pidOut = pid.Calculate(line_position, millis());
    driverLeft.setSpeed(MOTOR_BASE_SPEED_LEFT + pidOut);
    driverRight.setSpeed(MOTOR_BASE_SPEED_RIGHT - pidOut);
    break;
  }*/
}