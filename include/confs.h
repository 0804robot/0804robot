#ifndef CONNFS_h
#define CONNFS_h

#include <FCH.h>
#define MOTOR_BASE_SPEED_LEFT 96
#define MOTOR_BASE_SPEED_RIGHT 97.25

FCH driverLeft(2);
FCH driverRight(16);

int line_position;
#endif