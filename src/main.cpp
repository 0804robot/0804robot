#include <Arduino.h>
#include <PID.h>
#include <state_machine.h>
#include <obstacle_detector.h>
#include <confs.h>
#include <line_array.h>
#include <maze_solver.h>

PID pid(2.1, 0, 5);
state_machine sm;
Obstacle od(26, 13, 22, 17, 33, 25);
RobotState robotState;
Servo frontServo;
LineArray lineArray(34, 35, 32, 19, 23);
maze_solver mz(RIGHT_WALL, 11,11,11);

int previous_pos = 0;
int obstacle_count = 0;

void setup()
{
  // put your setup code here, to run once:
  lineArray.init();
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  od.init();
  frontServo.attach(21);
  sm.transition();
  pinMode(LED_BUILTIN, OUTPUT);
  delay(1000);
}

void loop()
{
  robotState = sm.getCurrentState();
  switch (robotState)
  {
  case RobotState::line_following:
  { 
    digitalWrite(LED_BUILTIN, LOW);
    line_position = lineArray.readValue(1);
    Serial.println(od.getDistance_front());
    if (line_position == 10 && od.getDistance_front() < 10.0)
    {
      sm.transition();
      break;
    }else if (line_position == 10) {
      line_position=0;
    }
      double pidOut = pid.Calculate(line_position, millis());
      Serial.print(" ");
      Serial.print(constrain(MOTOR_BASE_SPEED_LEFT + pidOut, 85, 101));
      Serial.print(" ");
      Serial.println(constrain(MOTOR_BASE_SPEED_RIGHT - pidOut, 85, 101));
      driverLeft.setSpeed(constrain(MOTOR_BASE_SPEED_LEFT + pidOut, 85, 101));
      driverRight.setSpeed(constrain(MOTOR_BASE_SPEED_RIGHT - pidOut, 85, 101));
    previous_pos = line_position;
    break;
  }
  case RobotState::stop_and_go:
  {
    digitalWrite(LED_BUILTIN, HIGH);
    driverLeft.brake();
    driverRight.brake();
    delay(3000);
    driverLeft.setSpeed(100);
    driverRight.setSpeed(80);
    delay(580);
    sm.transition();
    break;
  }

  //default:
    //driverLeft.brake();
    //driverRight.brake();
    //break;
  case RobotState::obstacle_avoidance:
  {
    digitalWrite(LED_BUILTIN, LOW);
    if (obstacle_count >= 3 || lineArray.lost_line_count >= 1){
      //if (obstacle_count >= 3 && lineArray.lost_line_count >= 1){ for actual track
      sm.transition();
      break;
    }
    if (od.getDistance_front() < 5.0)
    {
      driverLeft.brake();
      driverRight.brake();
      obstacle_count++;
      //digitalWrite(2, LOW);
      float distance_left, distance_right;
      frontServo.write(180);
      delay(200);
      distance_left = od.getDistance_left();
      frontServo.write(100);
      delay(200);
      distance_right = od.getDistance_right();
      frontServo.write(140);
      delay(200);
      Serial.print("Front: ");
      Serial.print(od.getDistance_front());
      Serial.print(" Left: ");
      Serial.print(distance_left);
      Serial.print(" Right: ");
      Serial.println(distance_right);
      if (distance_left > distance_right)
      {
        Drive60LeftRoutine();
        Drive60RightRoutine();
        Drive60RightRoutine();
      }
      else if (distance_right > distance_left)
      {
        Drive60RightRoutine();
        Drive60LeftRoutine();
        Drive60LeftRoutine();
      }
    }
    else
    {
      line_position = lineArray.readValue(2);
      if (line_position == 10)
      {
        line_position = previous_pos;
      }
      double pidOut = pid.Calculate(line_position, millis());
      //Serial.println(lineArray.readValue());
      driverLeft.setSpeed(constrain(MOTOR_BASE_SPEED_LEFT + pidOut, 85, 105));
      driverRight.setSpeed(constrain(MOTOR_BASE_SPEED_RIGHT - pidOut, 85, 105));
      if (line_position != previous_pos)
      {
        driverLeft.brake();
        driverRight.brake();
        delay(15);
      }
      previous_pos = line_position;
    }
    break;
  }
  case RobotState::maze:
  {
    digitalWrite(LED_BUILTIN, HIGH);
    if (od.getDistance_front() < 10) {
      driverLeft.brake();
      driverRight.brake();
      delay(500);
    }
    directions direction = mz.get_turn_directions(od.getDistance_front(), od.getDistance_right(), od.getDistance_left());
    switch (direction)
    {
    case RIGHT:{
      driverLeft.setSpeed(100);
      driverRight.setSpeed(80);
      delay(300);
      break;
    }
    case LEFT:{
      driverLeft.setSpeed(80);
      driverRight.setSpeed(100);
      delay(300);
      break;
    }
    case FOWARD:{
      driverLeft.setSpeed(MOTOR_BASE_SPEED_LEFT);
      driverRight.setSpeed(MOTOR_BASE_SPEED_RIGHT);
      break;
    }
    case TURN_AROUND:{
      driverLeft.setSpeed(100);
      driverRight.setSpeed(80);
      delay(290);
      break;
    }
    
    default:
      break;
    }
    break;
  }

  default:
    break;
  }
}