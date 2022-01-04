#include "Settings.hpp"

uint8_t BACKLIGHT_DURATION = 0;



void initSettingsParameters(){
	BACKLIGHT_DURATION = 10;
	//read from EEPROM
}

void setBackLightDuration(uint8_t durationS){
	BACKLIGHT_DURATION = durationS;
}
