#ifndef CONNFS_h
#define CONNFS_h

#include <FCH.h>
#define MOTOR_BASE_SPEED_LEFT 96
#define MOTOR_BASE_SPEED_RIGHT 96

#define IGNORED_CHECKPOINTS 1

FCH driverLeft(2);
FCH driverRight(16);

int line_position;

void Drive60LeftRoutine(void)
{
    driverLeft.setSpeed(80);
    driverRight.setSpeed(100);
    delay(300);
    driverLeft.setSpeed(MOTOR_BASE_SPEED_LEFT);
    driverRight.setSpeed(MOTOR_BASE_SPEED_RIGHT);
    delay(200);
}
void Drive60RightRoutine(void)
{
    driverLeft.setSpeed(100);
    driverRight.setSpeed(80);
    delay(300);
    driverLeft.setSpeed(MOTOR_BASE_SPEED_LEFT);
    driverRight.setSpeed(MOTOR_BASE_SPEED_RIGHT);
    delay(200);
}
#endif