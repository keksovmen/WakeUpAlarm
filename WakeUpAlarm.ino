#include <Arduino.h>
#include <avr/interrupt.h>
#include <avr/io.h>


#include "ProgrammState.hpp"
#include "State.hpp"
#include "LcdPrintFunctions.hpp"


// #define AUDIO_OUT 9





void setup(void){
	pinMode(RELE_OUT, OUTPUT);
	pinMode(ALARM_OUT, OUTPUT);
	digitalWrite(RELE_OUT, LOW);
	digitalWrite(ALARM_OUT, LOW);
	
	Serial.begin(9600);
	Serial.println("Starting");

	
	lcd.init();
	//DEBUG
	lcd.backlight();
	
	
	initState();
	initInputButtons();
	initRealTimeTimer();
	
	diodTask.startTimer(0);
	displayTask.startTimer(0);

	// tone(AUDIO_OUT, 1000);

}

void loop(void){
	if (isSecondPast()){
		uint8_t deltaTime = getDeltaTime();
		tasksLoop(deltaTime);
	}
	if (buttons.eventReady()){
		ButtonEvent event = buttons.getEvent();
		buttons.consumeEvent();
		Serial.print("Last button index ");
		Serial.print(event.buttonIndex);
		Serial.print(", duration in milliseconds ");
		Serial.println(event.holdMs);
		
		lcdLightHandler.handleEvent(event);
		getState()->handleEvent(event);
	}
	audioHandler.doActions();
}


void tasksLoop(uint8_t secondsPast){
	clock.consumeTime(secondsPast);
	
	for (int i = 0; i < TASK_VECTOR_SIZE; i++){
		taskVector[i].consumeTime(secondsPast);
	}
	alarms.consumeTime(secondsPast);
	lcdLightHandler.consumeTime(secondsPast);
	tempHandler.consumeTime(secondsPast);
}

// void wait(unsigned int ticksCount){
	// cli();
	// TCNT1 = 0x0000;
	// ticks = 0;
	// sei();
	// while(ticks < ticksCount){
		// ;
	// }	
// }

void printClock(){
	Serial.print(clock.getTime().hours);
	Serial.print(":");
	Serial.print(clock.getTime().minutes);
	Serial.print(":");
	Serial.print(clock.getTime().seconds);
	Serial.print(" ");
	Serial.print(clock.getDate().day);
	Serial.print(".");
	Serial.print(clock.getDate().month);
	Serial.print(".");
	Serial.print(clock.getDate().year);
	Serial.print(" ");
	Serial.println(clock.getDate().currentDay);
}

