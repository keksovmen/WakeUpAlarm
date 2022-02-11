#include "State.hpp"
#include "LcdPrintFunctions.hpp"
#include "ProgrammState.hpp"
#include "PinOUT.h"


AlarmState::AlarmState(uint8_t alarmId)
	: alarmId(alarmId)
{
	digitalWrite(ALARM_RELE_PIN, HIGH);
}

void AlarmState::actOnEvents(){
	//do nothing
}

void AlarmState::handleEvent(const ButtonEvent& event){
	digitalWrite(ALARM_RELE_PIN, LOW);
	alarms.disableAlarmAutoOff();
	audioHandler.deactivate();
	setState(StateFactory::createDefaultState());
}