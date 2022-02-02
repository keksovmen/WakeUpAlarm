#include "State.hpp"
#include "LcdPrintFunctions.hpp"
#include "ProgrammState.hpp"




DefaultState::DefaultState(){
	lcd.cursor_off();
	lcd.clear();
	displayTask.startTimer(0);
}


void DefaultState::handleEvent(const ButtonEvent& event){
	if (event.holdMs >= 1000){
		switch(event.buttonIndex){
			case 0:
				alarms.flipAlarm((event.holdMs / 1000) - 1);
				printHomePage(clock);
				break;
			case 1:
				lcdLightHandler.enableBackLight();
				break;
			case 2:
				setState(StateFactory::createMenuState());
				break;
			case 3:
				tempHandler.forceMeasure();
				break;
		}
	}
}