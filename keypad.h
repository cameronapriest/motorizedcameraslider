#ifndef KEYPAD_H_
#define KEYPAD_H_

#define ROW0 BIT0   // P3.0
#define ROW1 BIT5   // P3.5
#define ROW2 BIT6   // P3.6
#define ROW3 BIT7   // P3.7

#define COL0 BIT0   // P5.0
#define COL1 BIT1   // P5.1
#define COL2 BIT2   // P5.2
#define COL3 BIT6   // P5.6

#define NUM_COLS 4
#define SAFEGUARD_IN_US 150

/* this is simply a bit that is not sequential along with the
 * other three bits used for the columns (see COL3 macro pin
 * assignment above). I just utilized the sequential nature of
 * pins 5.0-2 while iterating, but could not do so for COL3. */
#define ROGUE_PIN_COLUMN 3

void initializeKeypad();   // initialize pins for the keypad
uint8_t detectKeypress();  // detect & determine keypresses

#endif /* KEYPAD_H_ */
