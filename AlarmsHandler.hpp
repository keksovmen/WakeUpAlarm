#ifndef ALARMS_HANDLER_H
#define ALARMS_HANDLER_H

#include <stdint.h>
#include "TimeConsumer.hpp"
#include "Timer.hpp"
#include "Clock.hpp"


#define TOTAL_ALARMS 3

#define MIN_AUTO_OFF_PERIOD 10
#define MAX_AUTO_OFF_PERIOD 3600
#define DEFAULT_AUTO_OFF_PERIOD 300

#define MIN_AUDIO_DELAY 0
#define MAX_AUDIO_DELAY MAX_AUTO_OFF_PERIOD - MIN_AUTO_OFF_PERIOD
#define DEFAULT_AUDIO_DELAY 5


template<uint8_t N>
class AlarmsHandler : public TimeConsumer{
	public:
		AlarmsHandler(const Time& currentTime);
		void consumeTime(int32_t deltaTime) override;
		
		void init();
		
		void activateAlarm(uint8_t alarmId);
		void deactivateAlarm(uint8_t alarmId);
		void flipAlarm(uint8_t alarmId);
		
		void setAlarmTime(const Time& time, uint8_t alarmId);
		const Time& getAlarmTime(uint8_t alarmId) const;
		bool isAlarmActivated(uint8_t alarmId) const;
		bool isAnyActivated() const;
		
		void setAlarmOffAfter(uint16_t delayS);
		const uint16_t& getAlarmOffAfter() const;
		void disableAlarmAutoOff();
		
		void setAudioDelay(uint16_t delayS);
		const uint16_t& getAudioDelay() const;
		
		void updateAlarmTimers();
		
	private:
		const Time& currentTime;
		
		Timer alarmsTimers[N];
		Time alarmsTimes[N];
		
		Timer alarmOffTimer;
		uint16_t alarmOffAfterS;
		
		Timer audioDelayTimer;
		uint16_t audioDelayS;
};




template class AlarmsHandler<TOTAL_ALARMS>;

#endif