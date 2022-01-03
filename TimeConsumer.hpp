#ifndef TIME_CONSUMER_H
#define TIME_CONSUMER_H


#include <stdint.h>

class TimeConsumer{
	public:
		virtual void consumeTime(int32_t deltaTime) = 0;
};


#endif