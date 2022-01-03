#include "AlarmsHandler.hpp"
#include "ProgrammState.hpp"
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
void AlarmsHandler<N>::flipAlarm(uint8_t alarmId){
	if(alarmId >= N){
		return;
	}
	if(isAlarmActivated(alarmId)){
		deactivateAlarm(alarmId);
	}else{
		activateAlarm(alarmId);
	}
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

template<uint8_t N>
bool AlarmsHandler<N>::isAlarmActivated(uint8_t alarmId) const{
	if(alarmId >= N){
		return false;
	}
	return alarmsTimers[alarmId].isActivated();
}

template<uint8_t N>
bool AlarmsHandler<N>::isAnyActivated() const{
	for (uint8_t i = 0; i < N; i++){
		if(alarmsTimers[i].isActivated()){
			return true;
		}
	}
	return false;
}