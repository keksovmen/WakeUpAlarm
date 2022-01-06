#include "State.hpp"
#include "LcdPrintFunctions.hpp"
#include "ProgrammState.hpp"


AlarmState::AlarmState(uint8_t alarmId)
	: alarmId(alarmId)
{
	digitalWrite(ALARM_OUT, HIGH);
	lcd.cursor_off();
	lcd.clear();
	displayTask.startTimer(0);
}

void AlarmState::handleEvent(const ButtonEvent& event){
	if (event.holdMs >= 1000){
		digitalWrite(ALARM_OUT, LOW);
		alarms.disableAlarmAutoOff();
		audioHandler.deactivate();
		setState(StateFactory::createDefaultState());
	}
}