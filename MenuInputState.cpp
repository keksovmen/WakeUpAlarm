// #include <New.h>
#include "State.hpp"
#include "LcdPrintFunctions.hpp"
#include "ProgrammState.hpp"
#include "Settings.hpp"

//remember current lcd has 16 symbols on the line
static const char* MENUS[3]={
						"Set time",
						"Set date",
						"Set alarm time "};


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
				setState(StateFactory::createInputTimeState(setTime, clock.getTime()));
				return;
			case 1:
				setState(StateFactory::createInputDateState(setDate, clock.getDate()));
				return;
			case 2: 
				setState(StateFactory::createInputTimeState(
					[](const Time& t){
							setAlarmTime(t, 0);
							setState(StateFactory::createDefaultState());
						}, getAlarmTime(0)));
				return;
			case 3:
				setState(StateFactory::createInputTimeState(
					[](const Time& t){
							setAlarmTime(t, 1);
							setState(StateFactory::createDefaultState());
						}, getAlarmTime(1)));
				return;
		}
	}
	lcdShowInput();
}

int8_t MenuInputState::maxCursorPosition() const {
	return 3;
}


void MenuInputState::lcdShowInput() const {
	lcd.clear();
	if (cursorPosition >= 2){
		lcd.print(MENUS[2]);
		lcd.print(cursorPosition - 1);
	}else{
		lcd.print(MENUS[cursorPosition]);
	}
}