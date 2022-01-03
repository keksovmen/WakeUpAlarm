#include "State.hpp"
#include "LcdPrintFunctions.hpp"
#include "ProgrammState.hpp"
#include "Settings.hpp"


AlarmState::AlarmState(uint8_t alarmId)
	: alarmId(alarmId)
{
	digitalWrite(ALARM_OUT, HIGH);
	disableAlarmTask.startTimer(ALARM_AUTO_OFF_DURATION);
}
//TODO: auto disable task fire only after alarm state set,
//not when you setting alarm, that way you only need 1 disable
void AlarmState::handleInput(const ButtonEvent& event){
	if (event.holdMs >= 1000){
		digitalWrite(ALARM_OUT, LOW);
		disableAlarmTask.disable();
		setState(StateFactory::createDefaultState());
	}
}