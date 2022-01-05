#include <EEPROM.h>
#include "AlarmsHandler.hpp"
#include "ProgrammState.hpp"
#include "State.hpp"
#include "EepromPositions.h"



template<uint8_t N>
void AlarmsHandler<N>::init(){
	//read alarmsTimes from EEPROM
	EEPROM.get(ALARM_OFF_AFTER_ADDRESS, alarmOffAfterS);
	if(alarmOffAfterS > MAX_AUTO_OFF_PERIOD ||
		alarmOffAfterS < MIN_AUTO_OFF_PERIOD){
			setAlarmOffAfter(DEFAULT_AUTO_OFF_PERIOD);
	}
	for (uint8_t i = 0; i < TOTAL_ALARMS; i++){
		EEPROM.get(ALARMS_TIME_BEGINING_ADDRESS + i * sizeof(Time),
					alarmsTimes[i]);
		validateAndFixTime(alarmsTimes[i]);
	}
	
}


template<uint8_t N>
void AlarmsHandler<N>::consumeTime(int32_t deltaTime){
	for (uint8_t i = 0; i < N; i++){
		alarmsTimers[i].consumeTime(deltaTime);
		if(alarmsTimers[i].eventReady()){
			alarmsTimers[i].consumeEvent();
			alarmOffTimer.startTimer(alarmOffAfterS + deltaTime);
			setState(StateFactory::createAlarmState(i));
		}
	}
	alarmOffTimer.consumeTime(deltaTime);
	if (alarmOffTimer.eventReady()){
		alarmOffTimer.consumeEvent();
		//turn off alarm
		getState()->handleEvent(ButtonEvent(0, 1000));
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
	EEPROM.put(ALARMS_TIME_BEGINING_ADDRESS + alarmId * sizeof(Time),
				alarmsTimes[alarmId]);
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

template<uint8_t N>
void AlarmsHandler<N>::setAlarmOffAfter(uint16_t delayS){
	alarmOffAfterS = delayS;
	EEPROM.put(ALARM_OFF_AFTER_ADDRESS, alarmOffAfterS);
}

template<uint8_t N>
void AlarmsHandler<N>::disableAlarmAutoOff(){
	alarmOffTimer.disable();
}

template<uint8_t N>
const uint16_t& AlarmsHandler<N>::getAlarmOffAfter() const{
	return alarmOffAfterS;
}
