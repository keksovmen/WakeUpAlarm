#include "ButtonsControl.hpp"
#include <avr/interrupt.h>
#include <avr/io.h>


static volatile uint16_t ticks;
/**
	Calculate as (F_CPU / Timer2 divider) * period in ms
		- try to find proper period to get natural number,
		- result must be less than timer resolution,
			for timer 2 is 8 bit so 256 is max
	For this value:
		F_CPU = 16_000_000
		Timer2 divide = 1024
		Period in ms = 0.0016
**/
static const uint8_t BOUNDARY = 250;
static const uint8_t TICK_MULTIPLAYER = 16;

static void enableClock(void);
static void disableClock(void);



template<uint8_t N>
ButtonsControl<N>::ButtonsControl(){
	for (uint8_t i = 0; i < N; i++){
		states[i] = false;
	}
}
	
template<uint8_t N>	
void ButtonsControl<N>::activate(uint8_t buttonIndex){
	// assert that index always in bound
	if (buttonIndex >= N || buttonIndex < 0){
		return;
	}
	if (!activated && !states[buttonIndex]){
		enableClock();
		
		states[buttonIndex] = true;
		activated = true;
	}
}

template<uint8_t N>
void ButtonsControl<N>::deactivate(uint8_t buttonIndex){
	if (states[buttonIndex]){
		disableClock();
		
		states[buttonIndex] = false;
		button = ButtonEvent(buttonIndex, ticks * TICK_MULTIPLAYER);
		generateEvent();
		activated = false;
	}
}

template<uint8_t N>
void ButtonsControl<N>::deactivateAll(){
	//just speed up a bit
	if(!activated){
		return;
	}
	for (uint8_t i = 0; i < N; i++){
		deactivate(i);
	}
}

template<uint8_t N>
ButtonEvent ButtonsControl<N>::getEvent() const{
	return button;
}

//------------------------------------

static void enableClock(void){
	cli();
	ticks = 0;
	TCNT2 = 0;
	TCCR2A = (1 << WGM21);
	TCCR2B = (1 << CS20)|(1 << CS21)|(1 << CS22);
	OCR2A = BOUNDARY;
	TIMSK2 = (1 << OCIE2A);
	sei();
}

static void disableClock(void){
	uint8_t oldSREG = SREG;
	cli();
	TIMSK2 = 0;
	SREG = oldSREG;
}

ISR(TIMER2_COMPA_vect){
	ticks++;
}
