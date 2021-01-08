#include "input.h"
#include "timelapse.h"
#include "video.h"
#include "LCD.h"
#include "keypad.h"
#include "msp.h"
#include "delay.h"

uint16_t getUserInput() {
    char frames[DIGITS] = {'X', 'X', 'X', 'X'};
    uint8_t i = 0;
    while (1) {
        char key = detectKeypress();
        if (key != 0x45) {
            if (key == '*') {
                break;
            }
            lcdWriteData(key);
            frames[i] = key;
            i++;
            delay_ms(ONE_SEC_IN_MS);     // delay 1 second to debounce
        }
    }

    // convert array of chars to int ( {'3', '0', '1', 'X'} -> 301 )
    uint8_t j = i - 1;
    uint16_t result = 0;
    for (i = 0; i < DIGITS; i++) {
        if (frames[i] == 'X') {
            return result;
        } else {
            result += powerOfTen(j) * (frames[i] - ASCII_CONVERSION);
        }
        j--;
    }
    return result;
}

uint32_t powerOfTen(uint8_t exponent) {
    uint8_t i;
    uint32_t result = 1;
    for (i = 0; i < exponent; i++) {
        result = result * 10;
    }
    return result;
}
