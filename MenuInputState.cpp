// #include <New.h>
#include "State.hpp"
#include "LcdPrintFunctions.hpp"
#include "ProgrammState.hpp"

// extern char stateStorage[13];

//remember current lcd has 16 symbols on the line
static const char* MENUS[3]={"Set alarm",
						"Set time",
						"Set date"};


void activateAlarm(const Time& t){
	int32_t diff = t.diff(clock.getTime());
	if (diff <= 0){
		diff = abs(diff) + SECONDS_IN_DAY;
	}
	// DEBUG
	Serial.println(diff);
	
	alarmTask.startTimer(diff);
	disableAlarmTask.startTimer(diff + 30);
	setState(StateFactory::createDefaultState());
}

void setDate(const Date& d){
	clock.setDate(d);
	// DEBUG
	Serial.print("Current day ");
	Serial.println(clock.getDate().currentDay);
	
	setState(StateFactory::createDefaultState());
}

void setTime(const Time& t){
	clock.setTime(t);
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
				setState(StateFactory::createInputTimeState(activateAlarm, Time()));
				return;
			case 1:
				setState(StateFactory::createInputTimeState(setTime, clock.getTime()));
				return;
			case 2:
				setState(StateFactory::createInputDateState(setDate, clock.getDate()));
				return;
		}
	}
	lcdShowInput();
}

int8_t MenuInputState::maxCursorPosition() const {
	return 2;
}


void MenuInputState::lcdShowInput() const {
	lcd.clear();
	lcd.print(MENUS[cursorPosition]);
}