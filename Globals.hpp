#ifndef GLOBALS_H
#define GLOBALS_H

#include <LiquidCrystal_I2C.h>

#include "EepromClock.hpp"
#include "Task.hpp"
#include "TaskVector.hpp"
#include "ButtonsControl.hpp"
#include "State.hpp"
#include "AlarmsHandler.hpp"
#include "LcdLightHandler.hpp"
#include "TemperatureSensor.hpp"
#include "AudioHandler.hpp"



//lcd specific
#define LCD_I2C_ADDRESS 0x27
#define LCD_TOTAL_COLUMNS 16
#define LCD_TOTAL_ROWS 2

extern LiquidCrystal_I2C lcd;

extern EepromClock clock;

//total buttons to allocate space
#define BUTTONS_COUNT 4
extern ThresholdButtonsControl<BUTTONS_COUNT> buttons;

// #define TOTAL_ALARMS 3
extern AlarmsHandler<TOTAL_ALARMS> alarms;
extern LcdLightHandler lcdLightHandler;
extern TemperatureSensor tempHandler;
extern AudioHandler audioHandler;
extern State* state;


//state explicit calls for easing tracking
void setState(State* s);
State* getState();

#endif