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

//pin out
#define DIOD_BLINK_PIN 13
#define ALARM_RELE_PIN 8
#define TEMPERATURE_PROBE_PIN 10
#define AUDIO_PIN 9

//total buttons to allocate space
#define BUTTONS_COUNT 4
//what hold duration is minimal to accept in millis
#define THRESHOLD 50u

//task declarations
#define TASK_VECTOR taskVector

#define diodTask TASK_VECTOR[DIOD_TASK]
#define displayTask TASK_VECTOR[DISPLAY_TASK]
#define dateAutoSaveTask TASK_VECTOR[DATE_AUTO_SAVE]


extern LiquidCrystal_I2C lcd;

extern Clock clock;
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
void displayRoutine();
void autoSaveDateRoutine();



//1 sec timer1 functional
void initRealTimeTimer();
uint8_t getDeltaTime();
bool isSecondPast();

//buttons functionality
void initInputButtons();


//state explicit calls for easing tracking
void setState(State* s);
State* getState();

//for writing to EEPROM
void setCurrentDate(const Date& d);
void setCurrentTime(const Time& t);

#endif