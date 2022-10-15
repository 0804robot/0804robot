#ifndef CONNFS_h
#define CONNFS_h
#include <Satima.h>
#define MOTOR_BASE_SPEED_LEFT 80
#define MOTOR_BASE_SPEED_RIGHT 104

int line_position;

void Drive60LeftRoutine(Satima leftDriver, Satima rightDriver){
    leftDriver.setSpeed(104, CLOCKWISE);
    rightDriver.setSpeed(20, CLOCKWISE);
    delay(20);
    leftDriver.setSpeed(104, CLOCKWISE);
    rightDriver.setSpeed(80, CLOCKWISE);
    delay(20);
    leftDriver.brake(BRAKE);
}
void Drive60RightRoutine(Satima leftDriver, Satima rightDriver){
    leftDriver.setSpeed(104, CLOCKWISE);
    rightDriver.setSpeed(20, CLOCKWISE);
    delay(20);
    leftDriver.setSpeed(104, CLOCKWISE);
    rightDriver.setSpeed(80, CLOCKWISE);
    delay(20);
    leftDriver.brake(BRAKE);
}
#endif