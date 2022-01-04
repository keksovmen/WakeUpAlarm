#include "State.hpp"
#include "LcdPrintFunctions.hpp"
#include "ProgrammState.hpp"



#define ALARMS_MENUS_OFFSET 4
//remember current lcd has 16 symbols on the line
static const char* MENUS[5]={
						"Set time",
						"Set date",
						"Set backlight",
						"Set off period",
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

void setBackLight(const int16_t& s){
	lcdLightHandler.setBackLightDuration(s);
	setState(StateFactory::createDefaultState());
}

void setAlarmOffAfter(const int16_t& s){
	alarms.setAlarmOffAfter(s);
	setState(StateFactory::createDefaultState());
}




MenuInputState::MenuInputState(){
	lcdShowInput();
}

void MenuInputState::handleEvent(const ButtonEvent& event){
	CursorInputState::handleEvent(event);
	if (isCancelEvent(event)){
		// setState(StateFactory::createDefaultState());
		return;
	}
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
				setState(StateFactory::createInputIntState(setBackLight,
							MIN_BACK_LIGHT_DURATION,
							MAX_BACK_LIGHT_DURATION,
							lcdLightHandler.getBackLightDuration()));
				return;
			case 3:
				setState(StateFactory::createInputIntState(setAlarmOffAfter,
							MIN_AUTO_OFF_PERIOD,
							MAX_AUTO_OFF_PERIOD,
							alarms.getAlarmOffAfter()));
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
	return 3 + TOTAL_ALARMS;
}


void MenuInputState::lcdShowInput() const {
	lcd.clear();
	switch(cursorPosition){
		case 0: case 1:
			lcd.print(MENUS[cursorPosition]);
			break;
		case 2:
			lcd.print(MENUS[cursorPosition]);
			lcd.setCursor(0, 1);
			lcd.print(lcdLightHandler.getBackLightDuration());
			break;
		case 3:
			lcd.print(MENUS[cursorPosition]);
			lcd.setCursor(0, 1);
			lcd.print(alarms.getAlarmOffAfter());
			break;
		default:
			lcd.print(MENUS[ALARMS_MENUS_OFFSET]);
			lcd.print(cursorPosition - (ALARMS_MENUS_OFFSET - 1));
			break;
	}
}