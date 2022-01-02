#include "Settings.hpp"

uint8_t BACKLIGHT_DURATION = 0;
uint8_t ALARM_AUTO_OFF_DURATION = 0;

static Time alarmTimeVector[ALARM_VECTOR_SIZE];


void initSettingsParameters(){
	BACKLIGHT_DURATION = 10;
	ALARM_AUTO_OFF_DURATION = 1;
	//read from EEPROM
	//alarmTimeVector
}

void setBackLightDuration(uint8_t durationS){
	BACKLIGHT_DURATION = durationS;
}

void setAlarmAutoOffAfter(uint8_t seconds){
	ALARM_AUTO_OFF_DURATION = seconds;
}

void setAlarmTime(const Time& time, uint8_t alarmId){
	if (alarmId >= ALARM_VECTOR_SIZE){
		return;
	}
	alarmTimeVector[alarmId] = time;
}

const Time& getAlarmTime(uint8_t alarmId){
	if (alarmId >= ALARM_VECTOR_SIZE){
		return alarmTimeVector[0];
	}
	return alarmTimeVector[ALARM_VECTOR_SIZE];
}