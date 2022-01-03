#include "Settings.hpp"

uint8_t BACKLIGHT_DURATION = 0;
uint8_t ALARM_AUTO_OFF_DURATION = 0;



void initSettingsParameters(){
	BACKLIGHT_DURATION = 10;
	ALARM_AUTO_OFF_DURATION = 30;
	//read from EEPROM
}

void setBackLightDuration(uint8_t durationS){
	BACKLIGHT_DURATION = durationS;
}

void setAlarmAutoOffAfter(uint8_t seconds){
	ALARM_AUTO_OFF_DURATION = seconds;
}
