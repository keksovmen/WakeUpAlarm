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
				if (event.holdMs >= 2000){
					//for second timer
					alarms.flipAlarm(1);
				}else{
					alarms.flipAlarm(0);
				}
				printHomePage(true);
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