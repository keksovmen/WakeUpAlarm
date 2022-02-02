#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

#include "ConsumableEvent.hpp"
#include "TimeConsumer.hpp"

//Will generate event with default code, when remainingDelay <= 0
class Timer : public ConsumableEvent, public TimeConsumer{
	public:
		virtual void consumeTime(int32_t deltaTime) override;
		virtual void startTimer(int32_t delay);
		
		void disable(){isActivatedFlag = false;};
		bool isActivated() const {return isActivatedFlag;};
		
	private:
		bool isActivatedFlag = false;
		int32_t remainingDelay = 0;
	
};

#endif