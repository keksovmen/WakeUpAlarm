#ifndef BUTTONS_CONTROL_H
#define BUTTONS_CONTROL_H

#include <stdint.h>
#include <stdbool.h>

struct ButtonEvent{
	ButtonEvent(uint8_t buttonIndex=0, uint16_t durationMs=0) :
		buttonIndex(buttonIndex), holdMs(durationMs){};
	uint8_t buttonIndex;
	uint16_t holdMs;
};


template<uint8_t N>
class ButtonsControl{
	public:
		ButtonsControl();
		
		void activate(uint8_t buttonIndex);
		void deactivate(uint8_t buttonIndex);
		void deactivateAll();
		
		void consumeEvent();
		
		bool eventReady() const;
		ButtonEvent getEvent() const;
		
	private:
		bool states[N];
		ButtonEvent button;
		bool hasEvent = false;
		bool activated = false;
};

template class ButtonsControl<4>;

#endif