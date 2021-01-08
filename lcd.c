#include "msp.h"
#include "LCD.h"
#include "delay.h"

/* these functions use delays that assume the clock has
   already been set to the desired frequency */

void clearAndDisplayLCD(char* lineOne, char* lineTwo) {
    lcdClear();
    Write_string_LCD(lineOne, 1);
    Write_string_LCD(lineTwo, 2);
}

void Initialize_LCD() {
    P2->OUT &= ~BIT6;           // Clear Pin 2.6 (Enable = 0)
    delay_us(20000, CS->CTL0);  // delay 20 ms, or 20000 us
    command(0x28);              // Function Set (4-bit)
    delay_us(37, CS->CTL0);     // delay 37 us
    command(0x06);              // Entry Mode Set
    lcdClear();                // Clear Display w/ 37 us delay
    delay_us(1520, CS->CTL0);   // delay 1.52 ms, or 1520 us
    command(0x0F);              // Display On
}

void lcdClear() {
    delay_us(37, CS->CTL0);     // delay 37 us
    command(0x01);              // Clear Display
}

void Home_LCD() {
    delay_us(37, CS->CTL0);     // delay 37 us
    command(0x80);              // cursor to first line
    delay_us(1000, CS->CTL0);
}

void nibble() {
    delay_us(1000, CS->CTL0);   // 1000 us (1000000 ns) delay for tAS [8]
    P2->OUT |= BIT6;            // set P2.6 high (Enable = 1)
    delay_us(1000, CS->CTL0);   // 1000 us (1000000 ns) delay for tWHE [8]
    P2->OUT &= ~BIT6;           // Clear P2.6 (Enable = 0)
    delay_us(100, CS->CTL0);
}

void command(uint8_t c) {
    P4->OUT = c;        // output upper nibble
    P2->OUT &= ~BIT4;   // clear P2.4 (RS = 0: Command)
    P2->OUT &= ~BIT5;   // clear P2.5 (RW = 0: Write)
    nibble();           // enable high, then low
    c = c << 4;         // shift lower nibble into upper
    P4->OUT = c;        // output previously lower nibble
    nibble();           // enable high, then low
}

void Write_char_LCD(char c) {
    P4->OUT = c;        // output upper nibble
    P2->OUT |= BIT4;    // set P2.4 high (RS = 1: Data)
    P2->OUT &= ~BIT5;   // clear P2.5 (RW = 0: Write)
    nibble();           // enable high, then low
    c = c << 4;         // shift lower nibble into upper
    P4->OUT = c;        // output previously lower nibble
    nibble();           // enable high, then low
}

void configurePins() {
    P2->SEL0 &= 0;      // P2.7-0 General purpose I/O       SEL0 -> 00000000
    P2->SEL1 &= 0;      // P2.7-0 General purpose I/O       SEL1 -> 00000000
    P2->DIR &= 0;       // P2.7-0 Zeroed Out                 DIR -> 00000000
    P2->DIR |= 0x70;    // P2.6-4 Output I/O Configuration   DIR -> 01110000

    P4->SEL0 &= 0;      // P4.7-0 General purpose I/O       SEL0 -> 00000000
    P4->SEL1 &= 0;      // P4.7-0 General purpose I/O       SEL1 -> 00000000
    P4->DIR &= 0;       // P4.7-0 Zeroed Out                 DIR -> 00000000
    P4->DIR |= 0xF0;    // P4.7-4 Output I/O Configuration   DIR -> 11110000
}

void Write_string_LCD(char *s, uint8_t lineNum) {
    if (lineNum == 1) {
        Home_LCD();             // go to top left for line 1
    } else if (lineNum == 2) {
        Line_two_LCD();         // go to bottom left for line 2
    }
    uint8_t i = 0;
    while (s[i] != '\0') {
        Write_char_LCD(s[i]);   // write every character of the string
        i++;
    }
}

void Line_two_LCD() {
    delay_us(37, CS->CTL0);     // delay 37 us
    command(0xC0);              // cursor to second line
    delay_us(1000, CS->CTL0);
}
