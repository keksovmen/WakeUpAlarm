#include "State.hpp"
#include "LcdPrintFunctions.hpp"
#include "ProgrammState.hpp"
#include "Settings.hpp"


void printInt(const int16_t& val){
	Serial.println(val);
	setState(StateFactory::createDefaultState());
}



DefaultState::DefaultState(){
	lcd.cursor_off();
	lcd.clear();
	displayTask.startTimer(0);
}


void DefaultState::handleInput(const ButtonEvent& event){
	if (event.holdMs >= 1000){
		switch(event.buttonIndex){
			case 0:
				activateAlarm(getAlarmTime(0));
				break;
			case 1:
				lcd.backlight();
				disableBackLightTask.startTimer(5);
				break;
			case 2:
				setState(StateFactory::createMenuState());
				break;
			case 3:
				setState(StateFactory::createInputIntState(printInt, -40, -999, 9999));
				break;
		}
	}
}