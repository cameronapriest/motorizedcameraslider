#ifndef MOTOR_H_
#define MOTOR_H_

#define MOTOR P6
#define ENABLE BIT0
#define S1 BIT1
#define S2 BIT4
#define S3 BIT5
#define DIRECTION BIT6
#define STEP BIT7
// arbitrary identifiers for choosing parameters
#define ON 1
#define OFF 0
#define CW 0
#define CCW 1
#define FULL 1
#define HALF 2
#define QUARTER 4
#define EIGHTH 8
#define SIXTEENTH 16

extern uint8_t stepFactor;
void initializeMotor();             // initialize motor
void powerMotor(uint8_t status);    // ON or OFF
void setDirection(uint8_t dir);     // CW or CCW
void setStepType(uint8_t type);     // full -> sixteenth
void step(uint16_t steps);          // step motor

#endif /* MOTOR_H_ */