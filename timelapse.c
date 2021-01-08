#include "timelapse.h"
#include "input.h"
#include "msp.h"
#include "LCD.h"
#include "motor.h"
#include "delay.h"
#include "keypad.h"
#include <stdio.h>

uint8_t timelapse() {
    clearAndDisplayLCD("Timelapse Mode!", "# of Frames:");
    frames = getUserInput();
    // / by (frames - 1) b/c frames can be taken at start & end of each step
    uint16_t stepsPerFrame = MAX_STEPS / (frames - 1);
    delay_ms(1000);

    clearAndDisplayLCD("Seconds between", "Frames: ");
    uint16_t secondsBetweenFrames = getUserInput();
    delay_ms(1000);

    ccr = 750000 * secondsBetweenFrames / 64; // f(SMCLK) * seconds / 8 / 8
    printf("CCR %d\n", ccr);

    setDirection(CW);
    setStepType(SIXTEENTH); // smoother than whole steps
    numSteps = stepsPerFrame * stepFactor;

    preTLmessages();

    TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE; // TA CCR0 interrupt enabled
    TIMER_A0->CCR[0] = ccr;
    NVIC->ISER[0] |= 1 << ((TA0_0_IRQn) & 31); // Enable Timer A Interrupt 0

    SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk; // Enable sleep on exit from ISR
    __DSB(); // Ensures sleep on exit occurs immediately
    __sleep();  // sleep until sleep is disabled (i.e. timelapse is done)

    clearAndDisplayLCD("Timelapse", "completed!");
    while (detectKeypress() != '#');

    framesTaken = 0;
    return 0;
}

void initializeTimerA0() {
    TIMER_A0->CCTL[0] |= 0;
    TIMER_A0->CCR[0] = 0; // Initial CCR0 value

    // set to SMCLK, UP mode, SMCLK / 8
    TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_MC_1
            | TIMER_A_CTL_ID_3;
    TIMER_A0->EX0 = TIMER_A_EX0_TAIDEX_7; // SMCLK / 8 again

    __enable_irq(); // Enable global interrupt
    NVIC->ISER[0] &= ~(1 << ((TA0_0_IRQn) & 31)); // Disable T_A Interrupt 0
}

void preTLmessages() {
    clearAndDisplayLCD("Press * to start", "timelapse.");
    while (detectKeypress() != '*');

    clearAndDisplayLCD("Starting TL in", "3...");
    delay_ms(1000);
    Write_string_LCD("2...", 2);
    delay_ms(1000);
    Write_string_LCD("1...", 2);
    delay_ms(1000);

    clearAndDisplayLCD("Timelapse in", "progress.");
}
