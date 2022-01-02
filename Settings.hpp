#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdint.h>
#include "Clock.hpp"

#define ALARM_VECTOR_SIZE 2

//in seconds
extern uint8_t BACKLIGHT_DURATION;
//in seconds
extern uint8_t ALARM_AUTO_OFF_DURATION;


//setting functionality
//must call first, will init from EEPROM
void initSettingsParameters();


void setBackLightDuration(uint8_t durationS);
void setAlarmAutoOffAfter(uint8_t seconds);
void setAlarmTime(const Time& time, uint8_t alarmId);
const Time& getAlarmTime(uint8_t alarmId);

#endif