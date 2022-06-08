#ifndef TASK_H
#define TASK_H

#include <stdint.h>

#include "Timer.hpp"

class BaseTask : public Timer{
	public:
		void consumeTime(int32_t deltaTimeS) override;
		void startTimer(int32_t delayS) override;

	protected:
		virtual void actIfEvent() = 0;
	
	private:
		void tryEvent();
};

class Task : public BaseTask{
	public:
		Task(void (*activity)()) : activity(activity){};
	
	protected:
		void actIfEvent() override;

	private:
		void (*const activity)();
};






#endif