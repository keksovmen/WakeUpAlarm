#ifndef LCD_LIGHT_HANDLER_H
#define LCD_LIGHT_HANDLER_H

#include <stdint.h>

#include "EventHandler.hpp"
#include "ButtonsControl.hpp"
#include "TimeConsumer.hpp"
#include "Timer.hpp"



class LcdLightHandler : 
		public EventHandler<ButtonEvent>, 
		public TimeConsumer
{
	public:
		void handleEvent(const ButtonEvent& event) override;
		void consumeTime(int32_t deltaTime) override;
		
		void init();
		void enableBackLight();
		
		void setBackLightDuration(uint8_t durationS);
		const uint8_t& getBackLightDuration() const;
	
	private:
		Timer lightOffTimer;
		//in seconds
		uint8_t backLightDuration;
};


#endif