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
#include "AlarmsHandler.hpp"
#include "LcdLightHandler.hpp"
#include "TemperatureSensor.hpp"
#include "AudioHandler.hpp"


#define TIMER1_DIVIDER 1024
#define TIMER1_DIVIDER_REGISTER_VAL 0x05
#define TICKS_1S F_CPU / TIMER1_DIVIDER


#define RELE_OUT 13
#define ALARM_OUT 8
#define TEMPERATURE_PROBE_PIN 10
#define AUDIO_PIN 9

#define BUTTONS_COUNT 4


#define TASK_VECTOR taskVector

#define diodTask TASK_VECTOR[DIOD_TASK]
#define displayTask TASK_VECTOR[DISPLAY_TASK]



extern Clock clock;
extern LiquidCrystal_I2C lcd;

extern Task TASK_VECTOR[TASK_VECTOR_SIZE];
									
extern ButtonsControl<BUTTONS_COUNT> buttons;

extern State* state;

extern AlarmsHandler<TOTAL_ALARMS> alarms;

extern LcdLightHandler lcdLightHandler;

extern TemperatureSensor tempHandler;

extern AudioHandler audioHandler;


//init
void initState();

//task routines 
void diodRoutine();
void displayRoutine();



//1 sec timer1 functional
void initRealTimeTimer();
uint8_t getDeltaTime();
bool isSecondPast();

//buttons functionality
void initInputButtons();


//state explicit calls for easing tracking
void setState(State* s);
State* getState();



#endif