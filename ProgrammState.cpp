#include <EEPROM.h>
#include "ProgrammState.hpp"
#include "EepromPositions.h"

#define LCD_I2C_ADDRESS 0x27
#define LCD_TOTAL_COLUMNS 16
#define LCD_TOTAL_ROWS 2



LiquidCrystal_I2C lcd(LCD_I2C_ADDRESS,
						LCD_TOTAL_COLUMNS,
						LCD_TOTAL_ROWS);

Clock clock;
ThresholdButtonsControl<BUTTONS_COUNT> buttons(THRESHOLD);
Task TASK_VECTOR[TASK_VECTOR_SIZE] = {
							Task(diodRoutine),
							Task(displayRoutine),
							Task(autoSaveDateRoutine)
							};
AlarmsHandler<TOTAL_ALARMS> alarms(clock.getTime());
LcdLightHandler lcdLightHandler;
TemperatureSensor tempHandler(TEMPERATURE_PROBE_PIN);
AudioHandler audioHandler(AUDIO_PIN);
State* state = nullptr;


static Date readDateFromEEPROM(){
	Date d;
	EEPROM.get(DATE_ADDRESS, d);
	validateAndFixDate(d);
	return d;
}


void initProgramState(){
	clock.setDate(readDateFromEEPROM());
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
	autoSaveDateRoutine();
}

void setCurrentTime(const Time& t){
	clock.setTime(t);
	autoSaveDateRoutine();
	alarms.updateAlarmTimers();
}
