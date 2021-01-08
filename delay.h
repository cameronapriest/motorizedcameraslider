#ifndef DELAY_H_
#define DELAY_H_

#define FREQ_750_KHz 1500000    // will be divided by 2
#define FREQ_3_MHz 3000000
#define FREQ_6_MHz 6000000
#define FREQ_12_MHz 12000000
#define FREQ_24_MHz 24000000
#define DIVISOR 65536           // 0x10000 in decimal
#define INHERENT_DELAY 40
#define TWELVE 12               // found by trial & error w/ AD2

void delay_us(uint32_t microseconds, uint32_t frequency);
void delay_ms(uint32_t ms);
void set_DCO(uint32_t frequency);

#endif /* DELAY_H_ */
