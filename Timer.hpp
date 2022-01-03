#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

#include "ConsumableEvent.hpp"
#include "TimeConsumer.hpp"


class Timer : public ConsumableEvent, public TimeConsumer{
	public:
		void consumeTime(int32_t deltaTime) override;
		void startTimer(int32_t delay);
		
		void disable(){isActivatedFlag = false;};
		bool isActivated() const {return isActivatedFlag;};
		
	private:
		bool isActivatedFlag = false;
		int32_t remainingDelay = 0;
	
};

#endif