#ifndef PROGRAMM_STATE_H
#define PROGRAMM_STATE_H

#include <Arduino.h>
#include <stdint.h>
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


//total buttons to allocate space
#define BUTTONS_COUNT 4
//what hold duration is minimal to accept in millis
#define THRESHOLD 50u

//task declarations
#define TASK_VECTOR taskVector

#define diodTask TASK_VECTOR[DIOD_TASK]

//lcd specific
#define LCD_I2C_ADDRESS 0x27
#define LCD_TOTAL_COLUMNS 16
#define LCD_TOTAL_ROWS 2

extern LiquidCrystal_I2C lcd;

extern EepromClock clock;
extern ThresholdButtonsControl<BUTTONS_COUNT> buttons;
extern Task TASK_VECTOR[TASK_VECTOR_SIZE];
extern AlarmsHandler<TOTAL_ALARMS> alarms;
extern LcdLightHandler lcdLightHandler;
extern TemperatureSensor tempHandler;
extern AudioHandler audioHandler;
extern State* state;



//init extern fields
void initProgramState();

//task routines 
void diodRoutine();

//buttons functionality
void initInputButtons();


//state explicit calls for easing tracking
void setState(State* s);
State* getState();

#endif