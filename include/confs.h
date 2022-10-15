#ifndef CONNFS_h
#define CONNFS_h
#include <FCH.h>
#define MOTOR_BASE_SPEED_LEFT 80
#define MOTOR_BASE_SPEED_RIGHT 104

int line_position;

void Drive60LeftRoutine(FCH leftDriver, FCH rightDriver){
    leftDriver.setSpeed(104);
    rightDriver.setSpeed(20);
    delay(20);
    leftDriver.setSpeed(104);
    rightDriver.setSpeed(80);
    delay(20);
    leftDriver.brake();
}
void Drive60RightRoutine(FCH leftDriver, FCH rightDriver){
    leftDriver.setSpeed(104);
    rightDriver.setSpeed(20);
    delay(20);
    leftDriver.setSpeed(104);
    rightDriver.setSpeed(80);
    delay(20);
    leftDriver.brake();
}
#endif