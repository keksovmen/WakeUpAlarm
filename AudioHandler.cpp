#include <Arduino.h>
#include <avr/pgmspace.h>
#include "AudioHandler.hpp"


#define NOTES_SIZE 98
static const int freqs[] PROGMEM = {174, 233, 174, 195, 220, 146, 146, 195, 174, 155, 174, 116, 116, 130, 130, 146, 155, 155, 174, 195, 220, 233, 261, 174, 293, 261, 233, 261, 174, 174, 233, 220, 195, 220, 146, 146, 195, 174, 155, 174, 116, 116, 233, 220, 195, 174, 293, 261, 233, 220, 233, 261, 174, 174, 233, 220, 195, 174, 195, 220, 146, 146, 233, 195, 220, 233, 195, 220, 233, 195, 233, 311, 311, 293, 261, 233, 261, 293, 233, 233, 261, 233, 220, 195, 220, 233, 195, 195, 233, 220, 195, 174, 116, 116, 174, 195, 220, 233};
static const int timings[] PROGMEM = {250, 500, 375, 125, 500, 250, 250, 500, 375, 125, 500, 250, 250, 500, 375, 125, 500, 375, 125, 500, 375, 125, 750, 250, 500, 375, 125, 500, 250, 250, 500, 375, 125, 500, 375, 125, 500, 375, 125, 500, 375, 125, 500, 375, 125, 1000, 1000, 250, 250, 250, 250, 750, 250, 1000, 1000, 250, 250, 250, 250, 750, 250, 1000, 500, 375, 125, 500, 375, 125, 500, 375, 125, 1000, 1000, 250, 250, 250, 250, 750, 250, 1000, 1000, 250, 250, 250, 250, 750, 250, 1000, 500, 375, 125, 500, 375, 125, 1000, 500, 500, 2000};
static const int delays[] PROGMEM = {278, 556, 417, 139, 556, 278, 278, 556, 417, 139, 556, 278, 278, 556, 417, 139, 556, 417, 139, 556, 417, 139, 833, 278, 556, 417, 139, 556, 278, 278, 556, 417, 139, 556, 417, 139, 556, 417, 139, 556, 417, 139, 556, 417, 139, 1111, 1111, 278, 278, 278, 278, 833, 278, 1111, 1111, 278, 278, 278, 278, 833, 278, 1111, 556, 417, 139, 556, 417, 139, 556, 417, 139, 1111, 1111, 278, 278, 278, 278, 833, 278, 1111, 1111, 278, 278, 278, 278, 833, 278, 1111, 556, 417, 139, 556, 417, 139, 1111, 556, 556, 2222};


void AudioHandler::doActions(){
	if(!isActivated){
		return;
	}
	long now = millis();
	long delta = now - prevTime;
	prevTime = now;
	
	delayTimer.consumeTime(delta);
	if (delayTimer.eventReady()){
		delayTimer.consumeEvent();
		playNote();
	}
}


void AudioHandler::activate(){
	isActivated = true;
	prevTime = millis();
	currentNote = 0;
	playNote();
}

void AudioHandler::deactivate(){
	isActivated = false;
	noTone(pin);
}

void AudioHandler::playNote(){
	if (currentNote >= NOTES_SIZE){
		currentNote = 0;
		delayTimer.startTimer(5000);
	}else{
		tone(pin, pgm_read_word(&freqs[currentNote]),
				pgm_read_word(&timings[currentNote]));
		delayTimer.startTimer(pgm_read_word(&delays[currentNote]));
		currentNote++;
	}
}