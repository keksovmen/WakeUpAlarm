#include <New.h>
#include "State.hpp"

static char stateStorage[13];


State* StateFactory::createDefaultState()
{
	return new(stateStorage)DefaultState();
}

State* StateFactory::createMenuState(){
	return new(stateStorage)MenuInputState();
}

State* StateFactory::createInputTimeState(void (*consumer)(const Time& val),
									const Time& initialValue)
{
	return new(stateStorage)TimeInputState(consumer, initialValue);
}										

State* StateFactory::createInputDateState(void (*consumer)(const Date& val),
									const Date& initialValue)
{
	return new(stateStorage)DateInputState(consumer, initialValue);
}

State* StateFactory::createInputIntState(void (*consumer)(const int16_t& val),
										int16_t minVal, 
										int16_t maxVal, 
										int16_t initialValue)
{
	return new(stateStorage)IntInputState(consumer,
								initialValue, minVal, maxVal);
}

State* StateFactory::createAlarmState(uint8_t alarmId){
	return new(stateStorage)AlarmState(alarmId);
}