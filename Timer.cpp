#include "Timer.hpp"

void Timer::startTimer(int32_t delay){
	if (delay == 0){
		generateEvent();
	}else{
		remainingDelay = delay;
		isActivatedFlag = true;
	}
}

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

