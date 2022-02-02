#include <EEPROM.h>
#include "TemperatureSensor.hpp"
#include "EepromPositions.h"


void TemperatureSensor::consumeTime(int32_t deltaTime){
	timer.consumeTime(deltaTime);
	if (timer.eventReady()){
		timer.consumeEvent();
		if (isAsked){
			//read result
			isAsked = false;
			setTemp();
		}else{
			//ask result
			isAsked = true;
			askTemp();
		}
	}
}


void TemperatureSensor::init(){
	sensor.begin();
	sensor.setResolution(13);
	sensor.setWaitForConversion(false);
	
	EEPROM.get(TEMPERATURE_REFRESH_PERIOD_ADDRESS, askPeriod);
	if(askPeriod > MAX_TEMPERATURE_PERIOD ||
		askPeriod < MIN_TEMPERATURE_PERIOD){
			setTemperaturePeriod(DEFAULT_TEMPERATURE_PERIOD);
	}
	timer.startTimer(0);
}

void TemperatureSensor::forceMeasure(){
	timer.startTimer(0);
	consumeTime(0);
}

void TemperatureSensor::setTemperaturePeriod(uint8_t period){
	askPeriod = period;
	EEPROM.put(TEMPERATURE_REFRESH_PERIOD_ADDRESS, askPeriod);
}

void TemperatureSensor::askTemp(){
	sensor.requestTemperatures();
	timer.startTimer(1);
}

void TemperatureSensor::setTemp(){
	temperature = sensor.getTempCByIndex(0);
	generateEvent();
	timer.startTimer(askPeriod);
}