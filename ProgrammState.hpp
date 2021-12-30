#ifndef PROGRAMM_STATE_H
#define PROGRAMM_STATE_H

#include <Arduino.h>
#include <stdint.h>
#include <LiquidCrystal_I2C.h>

#include "Clock.hpp"
#include "Task.hpp"
#include "TaskVector.hpp"
#include "ButtonsControl.hpp"
#include "State.hpp"


#define TIMER1_DIVIDER 1024
#define TIMER1_DIVIDER_REGISTER_VAL 0x05
#define TICKS_1S F_CPU / TIMER1_DIVIDER


#define RELE_OUT 13
#define ALARM_OUT 8

#define BUTTONS_COUNT 4

#define diodTask taskVector[DIOD_TASK]
#define clockTask taskVector[CLOCK_TASK]
#define displayTask taskVector[DISPLAY_TASK]
#define disableBackLightTask taskVector[DISABLE_BACKLIGHT_TASK]
#define alarmTask taskVector[ALARM_TASK]
#define disableAlarmTask taskVector[DISABLE_ALARM_TASK]


extern Clock clock;
extern LiquidCrystal_I2C lcd;

extern Task taskVector[TASK_VECTOR_SIZE];
									
extern ButtonsControl<BUTTONS_COUNT> buttons;

extern State* state;


//routines 
void diodRoutine();
void timeRoutine();
void displayRoutine();
void backlightRoutine();
void alarmRoutine();
void disableAlarmRoutine();


//1 sec timer1 functional
void initRealTimeTimer();
uint8_t getDeltaTime();
bool isSecondPast();

//buttons functionality
void initInputButtons();





//void disableDisplayTask(){}
//void enableDisplayTask(){}
#endif