#ifndef CONNFS_h
#define CONNFS_h

#include <FCH.h>
#define MOTOR_BASE_SPEED_LEFT 100
#define MOTOR_BASE_SPEED_RIGHT 100

#define IGNORED_CHECKPOINTS 3

FCH driverLeft(2);
FCH driverRight(16);

int line_position;

void Drive60LeftRoutine(void)
{
    driverLeft.setSpeed(90);
    driverRight.setSpeed(100);
    delay(600);
    driverLeft.brake();
    driverRight.brake();
    delay(200);
    driverLeft.setSpeed(MOTOR_BASE_SPEED_LEFT);
    driverRight.setSpeed(MOTOR_BASE_SPEED_RIGHT);
    delay(1000);
}
void Drive60RightRoutine(void)
{
    driverLeft.setSpeed(100);
    driverRight.setSpeed(90);
    delay(600);
    driverLeft.brake();
    driverRight.brake();
    delay(200);
    driverLeft.setSpeed(MOTOR_BASE_SPEED_LEFT);
    driverRight.setSpeed(MOTOR_BASE_SPEED_RIGHT);
    delay(1000);
}
#endif