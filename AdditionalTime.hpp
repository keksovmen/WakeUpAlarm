#ifndef AdditionalTime_H
#define AdditionalTime_H

#include "Task.hpp"

#define MIN_ADDITIONAL_TIME_PERIOD 0
#define MAX_ADDITIONAL_TIME_PERIOD 24l * 60l * 60l * 30l
#define DEFAULT_ADDITIONAL_TIME_PERIOD 24l * 60l * 60l * 1l

class AdditionalTime : public BaseTask
{
	public:
		void init();

		int32_t getPeriod() { return periodS; }
		void setPeriod(int32_t periodS);

	protected:
		void actIfEvent() override;
	
	private:
		int32_t periodS;
};

#endif
