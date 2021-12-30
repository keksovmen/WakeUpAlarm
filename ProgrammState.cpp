#include "ProgrammState.hpp"

Clock clock;
LiquidCrystal_I2C lcd(0x27, 16, 2);
Task taskVector[TASK_VECTOR_SIZE] = {
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
	state = State::getDefaultState();
}