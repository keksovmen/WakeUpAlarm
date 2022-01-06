#ifndef AUDIO_HANDLER_H
#define AUDIO_HANDLER_H

#include <stdint.h>
#include "Timer.hpp"



class AudioHandler{
	public:
		AudioHandler(int pin) : pin(pin){};
		void doActions();
		void activate();
		void deactivate();
		
	private:
		Timer delayTimer;
		uint16_t currentNote = 0;
		long prevTime = 0;
		bool isActivated = false;
		int pin;
		
		void playNote();
		
};



#endif