#include "msp.h"
#include "delay.h"

void delay_ms(uint32_t ms) {
    int i, j;
    for (j = ms; j > 0 ; j--) {
        for (i = 75; i > 0; i--);
            // 75 because 750,000 / 10,000 = 75
    }
}

void delay_us(uint32_t microseconds, uint32_t frequency) {
    uint32_t i, iterations, adjustment;

    adjustment = 1 << (frequency / DIVISOR); // shift left based on frequency

    // adjust due to inherent delay
    microseconds = microseconds - (INHERENT_DELAY / adjustment);
    // calculate number of iterations - 12 was based on trial & error w/ AD2
    iterations = microseconds * adjustment / TWELVE;

    for (i = iterations; i > 0; i--);
}

void set_DCO(uint32_t frequency) {
    CS->KEY = CS_KEY_VAL;           // unlock CS registers
    CS->CTL0 = 0;                   // clear register CTL0

    if (frequency == FREQ_750_KHz) {
        CS->CTL0 = CS_CTL0_DCORSEL_0;       // set DCO = 1.5 MHz
    } else if (frequency == FREQ_3_MHz) {
        CS->CTL0 = CS_CTL0_DCORSEL_1;       // set DCO = 3 MHz
    } else if (frequency == FREQ_6_MHz) {
        CS->CTL0 = CS_CTL0_DCORSEL_2;       // set DCO = 6 MHz
    } else if (frequency == FREQ_12_MHz) {
        CS->CTL0 = CS_CTL0_DCORSEL_3;       // set DCO = 12 MHz
    } else if (frequency == FREQ_24_MHz) {
        CS->CTL0 = CS_CTL0_DCORSEL_4;       // set DCO = 24 MHz
    }

    // select clock sources, divide by 2 (1.5 MHz -> 750 kHz)
    CS->CTL1 = CS_CTL1_SELA_2 | CS_CTL1_SELS_3 | CS_CTL1_SELM_3 | CS_CTL1_DIVS_1;
    CS->KEY = 0;                    // lock the CS registers
}
