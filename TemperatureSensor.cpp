#include "TemperatureSensor.hpp"


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
	//read from EEPROM
	askPeriod = 30;
	timer.startTimer(0);
}

void TemperatureSensor::forceMeasure(){
	timer.startTimer(0);
	consumeTime(0);
}

void TemperatureSensor::setTemperaturePeriod(uint8_t period){
	//write to EEPROM
	askPeriod = period;
}

void TemperatureSensor::askTemp(){
	sensor.requestTemperatures();
	timer.startTimer(1);
}

void TemperatureSensor::setTemp(){
	temperature = sensor.getTempCByIndex(0);
	timer.startTimer(askPeriod);
}