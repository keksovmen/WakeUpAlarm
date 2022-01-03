#include <stdbool.h>

class ConsumableEvent{
	public:
		void consumeEvent(){eventFlag = false;}
		void generateEvent(){eventFlag = true;}
		bool eventReady() const{return eventFlag;}
	private:
		bool eventFlag = false;
};