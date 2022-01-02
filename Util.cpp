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

int32_t pow10(int8_t power){
	int32_t result = 1;
	for (int i = 1; i < power; i++){
		result *= 10;
	}
	return result;
}