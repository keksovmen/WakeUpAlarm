#include "ProgrammState.hpp"

Clock clock;
LiquidCrystal_I2C lcd(0x27, 16, 2);
Task TASK_VECTOR[TASK_VECTOR_SIZE] = {
							Task(diodRoutine),
							Task(timeRoutine), 
							Task(displayRoutine),
							Task(backlightRoutine),
							Task(alarmRoutine),
							Task(disableAlarmRoutine)
							};
ButtonsControl<BUTTONS_COUNT> buttons;

State* state = nullptr;


void initState(){
	// lcd.init();
	setState(StateFactory::createDefaultState());
}

void setState(State* s){
	state = s;
}

State* getState(){
	return state;
}

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