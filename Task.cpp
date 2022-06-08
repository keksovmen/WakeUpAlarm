#include "Task.hpp"

void BaseTask::consumeTime(int32_t deltaTimeS){
	Timer::consumeTime(deltaTimeS);
	tryEvent();
}

void BaseTask::startTimer(int32_t delayS){
	Timer::startTimer(delayS);
	tryEvent();
}

void BaseTask::tryEvent(){
	if(eventReady()){
		consumeEvent();
		actIfEvent();
	}
}



void Task::actIfEvent(){
	activity();
}