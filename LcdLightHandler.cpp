#include "LcdLightHandler.hpp"
#include "ProgrammState.hpp"


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
	//read from EEPROM
	backLightDuration = 10;
}

void LcdLightHandler::enableBackLight(){
	lcd.backlight();
	lightOffTimer.startTimer(backLightDuration);
}

void LcdLightHandler::setBackLightDuration(uint8_t durationS){
	//write to EEPROM
	backLightDuration = durationS;
}


const uint8_t& LcdLightHandler::getBackLightDuration() const{
	return backLightDuration;
}