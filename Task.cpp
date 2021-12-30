#include "Task.hpp"

void Task::consumeTime(int32_t deltaTimeS){
	if (isActive == false){
		return;
	}
	remainingDelayS -= deltaTimeS;
	if (remainingDelayS <= 0){
		isActive = false;
		activity();
	}
}

void Task::startTimer(int32_t delayS){
	remainingDelayS = delayS;
	isActive = true;
}