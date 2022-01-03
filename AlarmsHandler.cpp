#include "AlarmsHandler.hpp"
#include "ProgrammState.hpp"
#include "Clock.hpp"
#include "State.hpp"



template<uint8_t N>
void AlarmsHandler<N>::init(){
	//read alarmsTimes from EEPROM
}


template<uint8_t N>
void AlarmsHandler<N>::consumeTime(int32_t deltaTime){
	for (uint8_t i = 0; i < N; i++){
		alarmsTimers[i].consumeTime(deltaTime);
		if(alarmsTimers[i].eventReady()){
			alarmsTimers[i].consumeEvent();
			setState(StateFactory::createAlarmState(i));
		}
	}
}

template<uint8_t N>
void AlarmsHandler<N>::activateAlarm(uint8_t alarmId){
	if(alarmId >= N){
		return;
	}
	int32_t diff = alarmsTimes[alarmId].diff(clock.getTime());
	if (diff <= 0){
		diff = abs(diff) + SECONDS_IN_DAY;
	}
	// DEBUG
	Serial.println(diff);
	alarmsTimers[alarmId].startTimer(diff);
}

template<uint8_t N>
void AlarmsHandler<N>::deactivateAlarm(uint8_t alarmId){
	if(alarmId >= N){
		return;
	}
	alarmsTimers[alarmId].disable();
}

template<uint8_t N>
void AlarmsHandler<N>::setAlarmTime(const Time& time, uint8_t alarmId){
	//write to EEPROM
	if(alarmId >= N){
		return;
	}
	alarmsTimes[alarmId] = time;
}

template<uint8_t N>
const Time& AlarmsHandler<N>::getAlarmTime(uint8_t alarmId) const{
	if(alarmId >= N){
		return alarmsTimes[0];
	}
	return alarmsTimes[alarmId];
}