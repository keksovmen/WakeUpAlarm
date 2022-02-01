#include "Timer.hpp"



void Timer::consumeTime(int32_t deltaTime){
	if (!isActivated() || deltaTime == 0){
		return;
	}
	remainingDelay -= deltaTime;
	if (remainingDelay <= 0){
		generateEvent();
		disable();
	}
}

void Timer::startTimer(int32_t delay){
	if (delay <= 0){
		generateEvent();
		isActivatedFlag = false;
	}else{
		remainingDelay = delay;
		isActivatedFlag = true;
	}
}
