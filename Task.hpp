#ifndef TASK_H
#define TASK_H

#include <stdbool.h>
#include <stdint.h>

class Task{
	public:
		Task(void (*activity)()) : activity(activity){};
		
		bool isActivated() const{return isActive;};
		void consumeTime(int32_t deltaTimeS);
		void startTimer(int32_t delayS);
		void disable(){isActive = false;};
		// Task(const void (*activity));
		
	private:
		void (*const activity)();
		
		bool isActive = false;
		//in seconds
		int32_t remainingDelayS = 0;
};






#endif