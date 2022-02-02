#include "ProgrammState.hpp"
#include "EepromPositions.h"



LiquidCrystal_I2C lcd(LCD_I2C_ADDRESS,
						LCD_TOTAL_COLUMNS,
						LCD_TOTAL_ROWS);

EepromClock clock(DATE_ADDRESS);
ThresholdButtonsControl<BUTTONS_COUNT> buttons(THRESHOLD);
Task TASK_VECTOR[TASK_VECTOR_SIZE] = {
							Task(diodRoutine)
							};
AlarmsHandler<TOTAL_ALARMS> alarms(clock.getTime());
LcdLightHandler lcdLightHandler;
TemperatureSensor tempHandler(TEMPERATURE_PROBE_PIN);
AudioHandler audioHandler(AUDIO_PIN);
State* state = nullptr;




void initProgramState(){
	alarms.init();
	lcdLightHandler.init();
	tempHandler.init();
	setState(StateFactory::createDefaultState());
}

void setState(State* s){
	state = s;
}

State* getState(){
	return state;
}

