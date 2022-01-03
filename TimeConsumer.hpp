#include <stdint.h>

class TimeConsumer{
	public:
		virtual void consumeTime(int32_t deltaTime) = 0;
};