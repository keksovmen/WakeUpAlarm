#include "ProgrammState.hpp"

/**
	Will use Timer1 in CTC mode,
	Boundary must be set to 1 second precisely
**/

static volatile uint8_t ticks = 0;


void initRealTimeTimer(){
	cli();
	TCCR1A = 0;
	TCCR1B = (1 << WGM12)|TIMER1_DIVIDER_REGISTER_VAL;
	OCR1A = TICKS_1S;
	TIMSK1 = (1 << OCIE1A);
	sei();
}

uint8_t getDeltaTime(){
	uint8_t oldSREG = SREG;
	cli();
	uint8_t result = ticks;
	ticks = 0;
	SREG = oldSREG;
	return result;
}

bool isSecondPast(){
	return ticks > 0;
}

ISR(TIMER1_COMPA_vect){
	ticks++;
}