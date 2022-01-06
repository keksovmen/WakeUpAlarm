#include <EEPROM.h>
#include "ProgrammState.hpp"
#include "EepromPositions.h"

Clock clock;
LiquidCrystal_I2C lcd(0x27, 16, 2);
Task TASK_VECTOR[TASK_VECTOR_SIZE] = {
							Task(diodRoutine),
							Task(displayRoutine),
							Task(autoSaveDate)
							};
ButtonsControl<BUTTONS_COUNT> buttons;

State* state = nullptr;

AlarmsHandler<TOTAL_ALARMS> alarms;

LcdLightHandler lcdLightHandler;

TemperatureSensor tempHandler(TEMPERATURE_PROBE_PIN);

AudioHandler audioHandler(AUDIO_PIN);


void initState(){
	Date d;
	EEPROM.get(DATE_ADDRESS, d);
	validateAndFixDate(d);
	clock.setDate(d);
	
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

void setCurrentDate(const Date& d){
	clock.setDate(d);
	autoSaveDate();
}

