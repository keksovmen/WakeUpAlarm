#include "Task.hpp"

void Task::consumeTime(int32_t deltaTimeS){
	Timer::consumeTime(deltaTimeS);
	actIfEvent();
}

void Task::startTimer(int32_t delayS){
	Timer::startTimer(delayS);
	actIfEvent();
}

void Task::actIfEvent(){
	if (eventReady()){
		consumeEvent();
		activity();
	}
}