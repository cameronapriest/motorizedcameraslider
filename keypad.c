#include "msp.h"
#include "keypad.h"
#include "LCD.h"
#include "delay.h"

const uint8_t arr[4][4] = {{'1', '4', '7', '*'}, {'2', '5', '8', '0'},
                           {'3', '6', '9', '#'}, {'A', 'B', 'C', 'D'}};

void initializeKeypad() {
    P3->SEL0 &= ~(ROW0 | ROW1 | ROW2 | ROW3);   // GPIO for P3.7-5, 0
    P3->SEL1 &= ~(ROW0 | ROW1 | ROW2 | ROW3);   // GPIO for P3.7-5, 0
    P3->DIR &= ~(ROW0 | ROW1 | ROW2 | ROW3);    // Set P3.7-5, 0 as input
    P3->REN |= (ROW0 | ROW1 | ROW2 | ROW3);     // Enable res. for P3.7-5, 0
    P3->OUT &= ~(ROW0 | ROW1 | ROW2 | ROW3);    // Pulldown r. for P3.7-5, 0

    P5->SEL0 &= ~(COL0 | COL1 | COL2 | COL3);   // GPIO for P5.6, 2-0
    P5->SEL1 &= ~(COL0 | COL1 | COL2 | COL3);   // GPIO for P5.6, 2-0
    P5->DIR |= (COL0 | COL1 | COL2 | COL3);     // Set P5.6, 2-0 as output
}

uint8_t detectKeypress()  {
    uint8_t i;

    P5->OUT |= (COL0 | COL1 | COL2 | COL3);     // set columns high
    delay_us(SAFEGUARD_IN_US);        // wait as a safeguard

    // if nothing is high, no buttons are pressed
    if ((P3->IN & (ROW0 | ROW1 | ROW2 | ROW3)) == 0) {
        return 0x45;    // return 'E' b/c it's not on the keypad
    }

    for (i = 0; i < NUM_COLS; i++) {    // iterate through all columns
        P5->OUT &= ~(COL0 | COL1 | COL2 | COL3);    // clear columns

        if (i == ROGUE_PIN_COLUMN) {
            P5->OUT |= COL3;        // set current column high
        } else {
            P5->OUT |= BIT0 << i;   // set current column high
        }
        delay_us(SAFEGUARD_IN_US);    // wait as a safeguard

        /* determine if a key in current column is pressed and return
           the key that is pressed */
        if (P3->IN & ROW0) {
            return arr[i][0];
        } else if (P3->IN & ROW1) {
            return arr[i][1];
        } else if (P3->IN & ROW2) {
            return arr[i][2];
        } else if (P3->IN & ROW3) {
            return arr[i][3];
        }
    }

    // no luck! something is probably wrong
    return 0x46;        // return 'F' b/c it's not on the keypad
}
