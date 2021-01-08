#include "msp.h"
#include "motor.h"
#include "LCD.h"
#include "delay.h"

void initializeMotor() {
    MOTOR->SEL1 &= ~(ENABLE | S1 | S2 | S3 | DIRECTION | STEP); // GPIO
    MOTOR->SEL0 &= ~(ENABLE | S1 | S2 | S3 | DIRECTION | STEP); // GPIO
    MOTOR->DIR |= ENABLE | S1 | S2 | S3 | DIRECTION | STEP;     // output
    MOTOR->OUT &= ~(S1 | S2 | S3 | STEP);   // Initialize output low
    MOTOR->OUT |= ENABLE | DIRECTION;       // En = 1 to disable, Dir = 1 CW
}

void powerMotor(uint8_t status) {
    if (status == ON) {
        MOTOR->OUT &= ~ENABLE;
    } else if (status == OFF) {
        MOTOR->OUT |= ENABLE;
    }
}

void setDirection(uint8_t dir) {
    if (dir == CW) {
        MOTOR->OUT |= DIRECTION;
    } else if (dir == CCW) {
        MOTOR->OUT &= ~DIRECTION;
    }
}

void setStepType(uint8_t type) {
    stepFactor = type;
    if (type == FULL) {
        MOTOR->OUT &= ~(S1 | S2 | S3);
    } else if (type == HALF) {
        MOTOR->OUT |= S1;
        MOTOR->OUT &= ~(S2 | S3);
    } else if (type == QUARTER) {
        MOTOR->OUT |= S2;
        MOTOR->OUT &= ~(S1 | S3);
    } else if (type == EIGHTH) {
        MOTOR->OUT |= S1 | S2;
        MOTOR->OUT &= ~S3;
    } else if (type == SIXTEENTH) {
        MOTOR->OUT |= S1 | S2 | S3;
    }
}

void step(uint16_t steps) {
    powerMotor(ON);
    uint8_t delay = 16 / stepFactor;
    int i;
    for (i = 0; i < steps; i++) {
        MOTOR->OUT |= STEP;
        delay_ms(delay);
        MOTOR->OUT &= ~STEP;
        delay_ms(delay);
    }
    powerMotor(OFF);
}
