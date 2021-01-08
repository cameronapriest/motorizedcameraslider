#ifndef LCD_H_
#define LCD_H_

void clearAndDisplayLCD(char* lineOne, char* lineTwo);
void configurePins();           // configures pins for I/O
void initializeLCD();           // initialize the LCD on start up
void lcdClear();               // clear the display
void Home_LCD();                // move the cursor to the top left of the LCD
void Line_two_LCD();            // move the cursor to the bottom left of LCD
void command(uint8_t c);        // give the LCD a command to execute
void Write_char_LCD(char c);    // write a character to the LCD
void nibble();                  // set enable high, delay, set enable low

// write a string to a specified location on the LCD
void Write_string_LCD(char *s, uint8_t lineNum);

#endif /* LCD_H_ */
