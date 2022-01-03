#include "ConsumableEvent.hpp"
#include <stdint.h>

class Timer : public ConsumableEvent{
	public:
		void startTimer(int32_t delay);
		void consumeTime(int32_t deltaTime);
		
		void disable(){isActivatedFlag = false;};
		bool isActivated() const {return isActivatedFlag;};
		
	private:
		bool isActivatedFlag = false;
		int32_t remainingDelay = 0;
	
};