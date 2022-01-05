#ifndef TEMPERATURE_SENSOR
#define TEMPERATURE_SENSOR

#include <stdint.h>
#include <OneWire.h>

#define REQUIRESALARMS false
#include <DallasTemperature.h>
#include "TimeConsumer.hpp"
#include "Timer.hpp"

#define MIN_TEMPERATURE_PERIOD 1
#define MAX_TEMPERATURE_PERIOD 60


class TemperatureSensor : public TimeConsumer
{
	public:
		TemperatureSensor(int sensorPin){
			oneWire = OneWire(sensorPin);
			sensor = DallasTemperature(&oneWire);
		}
		
		void consumeTime(int32_t deltaTime) override;
		void init();
		void forceMeasure();
		
		float getTemperature()const{return temperature;}
		
		void setTemperaturePeriod(uint8_t period);
		const uint8_t& getTemperaturePeriod() const {return askPeriod;}
		
		
	private:
		OneWire oneWire;
		DallasTemperature sensor;
		Timer timer;
	
		float temperature = DEVICE_DISCONNECTED_C;
		uint8_t askPeriod;
		bool isAsked = false;
		
		
		void askTemp();
		void setTemp();
		
		
		
};


#endif