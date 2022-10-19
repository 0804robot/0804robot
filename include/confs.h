#ifndef CONNFS_h
#define CONNFS_h
#include <FCH.h>
#define MOTOR_BASE_SPEED_LEFT 98
#define MOTOR_BASE_SPEED_RIGHT 97
FCH driverLeft(2);
FCH driverRight(16);

int line_position;

void Drive90LeftRoutine(void){
    driverLeft.setSpeed(100);
    driverRight.setSpeed(90);
    delay(500);
    driverLeft.brake();
    driverRight.brake();
    delay(1000);
    driverLeft.setSpeed(101);
    driverRight.setSpeed(100);
    delay(500);
    driverLeft.brake();
    driverRight.brake();
    delay(50);
}
void Drive90RightRoutine(void){
    driverLeft.setSpeed(90);
    driverRight.setSpeed(100);
    delay(450);
    driverLeft.brake();
    driverRight.brake();
    delay(50);
    driverLeft.setSpeed(96);
    driverRight.setSpeed(97);
    delay(500);
    driverLeft.brake();
    driverRight.brake();
    delay(50);
}
#endif