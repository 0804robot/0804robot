#ifndef CONNFS_h
#define CONNFS_h

#include <FCH.h>
#define MOTOR_BASE_SPEED_LEFT 100
#define MOTOR_BASE_SPEED_RIGHT 100

#define IGNORED_CHECKPOINTS 1

FCH driverLeft(2);
FCH driverRight(16);

int line_position;

void Drive60LeftRoutine(FCH leftDriver, FCH rightDriver){
    leftDriver.setSpeed(20);
    rightDriver.setSpeed(104);
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