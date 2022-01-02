#include "Util.hpp"

int8_t findLongLength(int32_t val){
	//max for 32 bits
	int32_t delimiter = 1000000000L;
	int8_t result = 1;
	bool started = false;
	
	while (delimiter > 1){
		int32_t tmp = val / delimiter;
		if (tmp > 0){
			started = true;
			val -= tmp * delimiter;
		}
		if(started){
			result++;
		}
		delimiter /= 10;
	}
	return result;
}