#ifndef TASK_H
#define TASK_H

// #include <stdbool.h>
// #include <stdint.h>
#include "Timer.hpp"

class Task : public Timer{
	public:
		Task(void (*activity)()) : activity(activity){};
		
		void consumeTime(int32_t deltaTimeS) override;
		void startTimer(int32_t delayS) override;
		
	private:
		void (*const activity)();
		
		void actIfEvent();
};






#endif