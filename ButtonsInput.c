#include "ButtonsInput.h"
#include <avr/io.h>
#include <avr/interrupt.h>

//hook to callback
static void (*consumer)(int8_t);


static void checkInput(){
	uint8_t state = PIND & 0xF0;
	if (state != 0xF0){
		if ((state & 0x10) == 0){
			consumer(0);
		}
		if ((state & 0x20) == 0){
			consumer(1);
		}
		if ((state & 0x40) == 0){
			consumer(2);
		}
		if ((state & 0x80) == 0){
			consumer(3);
		}
	}else{
		consumer(-1);
	}
}


void initInputButtons(void (*buttonConsumer)(int8_t)){
	consumer = buttonConsumer;
	
	//pins 4,5,6,7 on uno board
	DDRD = (0 << DDD4)|(0 << DDD5)|(0 << DDD6)|(0 << DDD7);
	PORTD = (1 << PORTD4)|(1 << PORTD5)|(1 << PORTD6)|(1 << PORTD7);
	
	//change interrupt on PCINT23,22,21,20
	//pins 4,5,6,7 on uno board
	PCICR = (1 << PCIE2);
	PCMSK2 = 0xF0;
}

ISR(PCINT2_vect){
	checkInput();
}