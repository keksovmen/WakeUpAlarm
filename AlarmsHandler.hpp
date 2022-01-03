#ifndef ALARMS_HANDLER_H
#define ALARMS_HANDLER_H

#include <stdint.h>
#include "TimeConsumer.hpp"
#include "Timer.hpp"
#include "Clock.hpp"

#define TOTAL_ALARMS 2



template<uint8_t N>
class AlarmsHandler : public TimeConsumer{
	public:
		void consumeTime(int32_t deltaTime) override;
		
		void init();
		
		void activateAlarm(uint8_t alarmId);
		void deactivateAlarm(uint8_t alarmId);
		
		void setAlarmTime(const Time& time, uint8_t alarmId);
		const Time& getAlarmTime(uint8_t alarmId) const;
		
	private:
		Timer alarmsTimers[N];
		Time alarmsTimes[N];
	
};




template class AlarmsHandler<TOTAL_ALARMS>;

#endif