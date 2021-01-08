#ifndef TIMELAPSE_H_
#define TIMELAPSE_H_

#define MAX_STEPS 2800

extern uint16_t frames;
extern uint16_t framesTaken;
extern uint32_t numSteps;
extern uint8_t stepFactor;
extern uint16_t ccr;

void preTLmessages();
uint8_t timelapse();
void initializeTimerA0();

#endif /* TIMELAPSE_H_ */
