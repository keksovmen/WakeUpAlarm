// #include <New.h>
#include "State.hpp"
#include "LcdPrintFunctions.hpp"
#include "ProgrammState.hpp"
#include "Settings.hpp"


#define ALARMS_MENUS_OFFSET 2
//remember current lcd has 16 symbols on the line
static const char* MENUS[3]={
						"Set time",
						"Set date",
						"Set alarm time "};
//cursed but does job
static uint8_t selectedAlarmId = 0;


void setTime(const Time& t){
	clock.setTime(t);
	setState(StateFactory::createDefaultState());
}

void setDate(const Date& d){
	clock.setDate(d);
	// DEBUG
	Serial.print("Current day ");
	Serial.println(clock.getDate().currentDay);
	
	setState(StateFactory::createDefaultState());
}

void setSelectedAlarmTime(const Time& t){
	alarms.setAlarmTime(t, selectedAlarmId);
	setState(StateFactory::createDefaultState());
}





MenuInputState::MenuInputState(){
	lcdShowInput();
}

void MenuInputState::handleInput(const ButtonEvent& event){
	CursorInputState::handleInput(event);
	if (event.buttonIndex == 0){
		//select
		switch(cursorPosition){
			case 0:
				setState(StateFactory::createInputTimeState(setTime, clock.getTime()));
				return;
			case 1:
				setState(StateFactory::createInputDateState(setDate, clock.getDate()));
				return;
			default:	//for alarms settings
				selectedAlarmId = cursorPosition - ALARMS_MENUS_OFFSET;
				setState(StateFactory::createInputTimeState(
						setSelectedAlarmTime,
						alarms.getAlarmTime(selectedAlarmId)));
				return;
		}
	}
	lcdShowInput();
}

int8_t MenuInputState::maxCursorPosition() const {
	return 1 + TOTAL_ALARMS;
}


void MenuInputState::lcdShowInput() const {
	lcd.clear();
	if (cursorPosition >= ALARMS_MENUS_OFFSET){
		lcd.print(MENUS[ALARMS_MENUS_OFFSET]);
		lcd.print(cursorPosition - (ALARMS_MENUS_OFFSET - 1));
	}else{
		lcd.print(MENUS[cursorPosition]);
	}
}