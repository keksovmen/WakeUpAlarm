#include <Arduino.h>


#include "Globals.hpp"
#include "EepromPositions.h"
#include "LcdPrintFunctions.hpp"
#include "PinOUT.h"
#include "RTC.h"
#include "ButtonsInput.h"



LiquidCrystal_I2C lcd(LCD_I2C_ADDRESS,
						LCD_TOTAL_COLUMNS,
						LCD_TOTAL_ROWS);

EepromClock clock(DATE_ADDRESS);
//what hold duration is minimal to accept in millis
#define THRESHOLD 50u
ThresholdButtonsControl<BUTTONS_COUNT> buttons(THRESHOLD);
AlarmsHandler<TOTAL_ALARMS> alarms(clock.getTime());
LcdLightHandler lcdLightHandler;
TemperatureSensor tempHandler(TEMPERATURE_PROBE_PIN);
AudioHandler audioHandler(AUDIO_PIN);
State* state = nullptr;
AdditionalTime additionalTime;


//hooks
void buttonsHook(int8_t key);


void initComponents();


void setup(void){
	pinMode(DIOD_BLINK_PIN, OUTPUT);
	pinMode(ALARM_RELE_PIN, OUTPUT);
	digitalWrite(DIOD_BLINK_PIN, LOW);
	digitalWrite(ALARM_RELE_PIN, LOW);
	
	Serial.begin(9600);
	Serial.println("Starting");

	
	lcd.init();
	//DEBUG
	
	
	initComponents();
	initInputButtons(buttonsHook);
	initRealTimeClock(PRESCALAR_1024, 1.0);
}

void loop(void){
	if (isTimePast()){
		tasksLoop(getDeltaTime());
	}
	if (buttons.eventReady()){
		ButtonEvent event = buttons.getEvent();
		buttons.consumeEvent();
		//DEBUG
		Serial.print("Last button index ");
		Serial.print(event.buttonIndex);
		Serial.print(", duration in milliseconds ");
		Serial.println(event.holdMs);
		
		lcdLightHandler.handleEvent(event);
		getState()->handleEvent(event);
	}
	audioHandler.doActions();
	getState()->actOnEvents();
}


void tasksLoop(uint8_t secondsPast){
	clock.consumeTime(secondsPast);
	alarms.consumeTime(secondsPast);
	lcdLightHandler.consumeTime(secondsPast);
	tempHandler.consumeTime(secondsPast);
	additionalTime.consumeTime(secondsPast);
}


void buttonsHook(int8_t key){
	if (key == -1){
		buttons.deactivateAll();
	}else{
		buttons.activate(key);
	}
}

void initComponents(){
	alarms.init();
	lcdLightHandler.init();
	tempHandler.init();
	additionalTime.init();
	setState(StateFactory::createDefaultState());
}


//---------------------------Globals---------------------------------------
void setState(State* s){
	state = s;
}

State* getState(){
	return state;
}

