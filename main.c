/* Cameron Priest
 * CPE 316 - Dr. Oliver
 * P3 – Motorized Camera Slider for Time-lapse and Video
 */

#include "msp.h"
#include "LCD.h"
#include "keypad.h"
#include "motor.h"
#include "input.h"
#include "timelapse.h"
#include "video.h"
#include "delay.h"
#include <stdio.h>
#include <stdlib.h>

#define TIMELAPSE 1
#define VIDEO 2

void promptUser();

uint8_t mode = 0;           // 1 = TL, 2 = Video
uint8_t stepFactor = 1;     // changes based on step type
uint16_t ccr = 0;           // ccr val for interrupt
uint32_t numSteps = 0;      // number of steps per frame
uint16_t framesTaken = 0;   // frames taken in current time-lapse
uint16_t frames = 0;        // number of total frames in time-lapse

void main(void) {
    set_DCO(FREQ_750_KHz);
    initializeTimerA0();
    initializeLCD();
    initializeKeypad();
    initializeMotor();
    promptUser();
}

void TA0_0_IRQHandler() {
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG; // clear interrupt flag

    step(numSteps);
    framesTaken++;
    if (framesTaken == frames) {
        TIMER_A0->CCTL[0] = 0;                          // disable interrupts
        NVIC->ISER[0] &= ~(1 << ((TA0_0_IRQn) & 31));   // disable interrupts
        SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;           // wake up from sleep
        __DSB();                                        // wake up from sleep
    }
}
void promptUser() {
    while (1) {
        clearAndDisplayLCD("Timelapse (1) or", "Video (2)");
        while (!mode) {
            char key = detectKeypress();
            if (key != 0x45) {
                if (key == '1') {
                    mode = TIMELAPSE;
                } else if (key == '2') {
                    mode = VIDEO;
                }
                delay_ms(1000);     // delay 1 second to debounce
            }
        }

        if (mode == TIMELAPSE) {
            mode = timelapse();
        } else if (mode == VIDEO) {
            mode = video();
        }
    }
}
