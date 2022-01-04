#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdint.h>
#include "Clock.hpp"

#define ALARM_VECTOR_SIZE 2

//in seconds
extern uint8_t BACKLIGHT_DURATION;



//setting functionality
//must call first, will init from EEPROM
void initSettingsParameters();


void setBackLightDuration(uint8_t durationS);


#endif