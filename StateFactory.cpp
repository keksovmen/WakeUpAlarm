#include <New.h>
#include "State.hpp"

static char stateStorage[13];


State* StateFactory::createDefaultState()
{
	return new(stateStorage)DefaultState();
}

State* StateFactory::createInputTimeState(void (*consumer)(const Time& val),
									bool initTimeWithClock)
{
	return new(stateStorage)TimeInputState(consumer, initTimeWithClock);
}										

State* StateFactory::createInputDateState(void (*consumer)(const Date& val))
{
	return new(stateStorage)DateInputState(consumer);
}

State* StateFactory::createAlarmState(){
	return new(stateStorage)AlarmState();
}

State* StateFactory::createMenuState(){
	return new(stateStorage)MenuInputState();
}

State* StateFactory::createInputIntState(void (*consumer)(const int16_t& val),
										int16_t minVal, 
										int16_t maxVal, 
										int16_t initialValue)
{
	return new(stateStorage)IntInputState(consumer,
								minVal, maxVal, initialValue);
}