#include <EEPROM.h>
#include "LcdLightHandler.hpp"
#include "Globals.hpp"
#include "EepromPositions.h"


void LcdLightHandler::handleEvent(const ButtonEvent& event){
	if (lightOffTimer.isActivated()){
		lightOffTimer.startTimer(backLightDuration);
	}
}

void LcdLightHandler::consumeTime(int32_t deltaTime){
	lightOffTimer.consumeTime(deltaTime);
	if(lightOffTimer.eventReady()){
		lightOffTimer.consumeEvent();
		lcd.noBacklight();
	}
}

void LcdLightHandler::init(){
	EEPROM.get(BACK_LIGHT_DURATION_ADDRESS, backLightDuration);
	if(backLightDuration > MAX_BACK_LIGHT_DURATION ||
		backLightDuration < MIN_BACK_LIGHT_DURATION){
			setBackLightDuration(DEFAULT_BACK_LIGHT_DURATION);
	}
}

void LcdLightHandler::enableBackLight(){
	lcd.backlight();
	lightOffTimer.startTimer(backLightDuration);
}

void LcdLightHandler::setBackLightDuration(uint8_t durationS){
	backLightDuration = durationS;
	EEPROM.put(BACK_LIGHT_DURATION_ADDRESS, backLightDuration);
}


const uint8_t& LcdLightHandler::getBackLightDuration() const{
	return backLightDuration;
}