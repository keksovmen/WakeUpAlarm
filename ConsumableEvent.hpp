#ifndef CONSUMABLE_EVENT_H
#define CONSUMABLE_EVENT_H

#include <stdbool.h>



class ConsumableEvent{
	public:
		void consumeEvent(){eventId = 0;}
		virtual void generateEvent(int eventId=1){this->eventId = eventId;}
		bool eventReady() const {return eventId != 0;}
		int getEventId() const {return eventId;}
	private:
		//default 0 implicit conversion to bool will give false
		//threat as no event exists
		int eventId = 0;
};

#endif