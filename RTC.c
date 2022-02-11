#include "RTC.h"
#include <avr/io.h>
#include <avr/interrupt.h>


static volatile uint8_t ticks = 0;


static uint16_t getPrescalarValue(enum Prescalars prescalar){
	switch (prescalar){
		case NO_PRESCALAR: return 1;
		case PRESCALAR_8: return 8;
		case PRESCALAR_64: return 64;
		case PRESCALAR_256: return 256;
		case PRESCALAR_1024: return 1024;
	}
}


void initRealTimeClock(enum Prescalars prescalar, float periodInSec){
	const uint16_t tickToInterapt = (F_CPU / getPrescalarValue(prescalar))
										* periodInSec;
	cli();
	TCCR1A = 0;
	TCCR1B = (1 << WGM12) | prescalar;
	OCR1A = tickToInterapt;
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

bool isTimePast(){
	return ticks > 0;
}

ISR(TIMER1_COMPA_vect){
	ticks++;
}