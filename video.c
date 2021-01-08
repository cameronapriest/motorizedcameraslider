#include "msp.h"
#include "video.h"
#include "input.h"
#include "motor.h"
#include "delay.h"
#include "timelapse.h"
#include "keypad.h"

uint8_t video() {
    clearAndDisplayLCD("Video Mode!", "");

    setStepType(SIXTEENTH);
    setDirection(CW);
    step(MAX_STEPS * stepFactor);
    setDirection(CCW);
    step(MAX_STEPS * stepFactor);

    return 0;
}
