#include "ProgrammState.hpp"

Clock clock;
LiquidCrystal_I2C lcd(0x27, 16, 2);
Task TASK_VECTOR[TASK_VECTOR_SIZE] = {
							Task(diodRoutine),
							Task(timeRoutine), 
							Task(displayRoutine),
							Task(backlightRoutine)
							};
ButtonsControl<BUTTONS_COUNT> buttons;

State* state = nullptr;

AlarmsHandler<TOTAL_ALARMS> alarms;

void initState(){
	alarms.init();
	setState(StateFactory::createDefaultState());
}

void setState(State* s){
	state = s;
}

State* getState(){
	return state;
}

