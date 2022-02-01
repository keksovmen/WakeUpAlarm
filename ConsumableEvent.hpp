#ifndef CONSUMABLE_EVENT_H
#define CONSUMABLE_EVENT_H

#include <stdbool.h>

class ConsumableEvent{
	public:
		void consumeEvent(){eventFlag = false;}
		virtual void generateEvent(){eventFlag = true;}
		bool eventReady() const{return eventFlag;}
	private:
		bool eventFlag = false;
};

#endif