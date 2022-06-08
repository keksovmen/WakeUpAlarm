#include <EEPROM.h>

#include "AdditionalTime.hpp"
#include "EepromPositions.h"
#include "Globals.hpp"


void AdditionalTime::init(){
	EEPROM.get(ADDITIONAL_SEC_PERIOD_ADDRESS, periodS);
	if(periodS < MIN_ADDITIONAL_TIME_PERIOD ||
		periodS > MAX_ADDITIONAL_TIME_PERIOD)
	{
		periodS = DEFAULT_ADDITIONAL_TIME_PERIOD;
	}
	if(periodS > 0) startTimer(periodS);
}

void AdditionalTime::setPeriod(int32_t periodS){
	this->periodS = periodS;
	EEPROM.put(ADDITIONAL_SEC_PERIOD_ADDRESS, periodS);
	if(periodS > 0) startTimer(periodS);
}

void AdditionalTime::actIfEvent(){
	clock.incrementSecond();
	startTimer(periodS);
}
