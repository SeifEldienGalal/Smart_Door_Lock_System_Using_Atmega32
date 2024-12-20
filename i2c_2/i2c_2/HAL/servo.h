#ifndef SERVO_H_
#define SERVO_H_

#include "../Application/std_types.h"

// Function to initialize servo PWM
void SERVO_init(void);

// Function to set servo angle (0-180 degrees)
void SERVO_setAngle(uint8 angle);

#endif /* SERVO_H_ */