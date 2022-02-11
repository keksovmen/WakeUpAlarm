#ifndef RTC_H
#define RTC_H

#include <stdint.h>
#include <stdbool.h>

/**
	Currently works only for Timer1 int CTC mode
	You need to specify prescalar and period in seconds
	Pre calculate value to see if it overflows 16 bit
**/


#ifdef __cplusplus
extern "C" {
#endif

//check documentation for Timer1
enum Prescalars {
	NO_PRESCALAR = 1,
	PRESCALAR_8 = 2,
	PRESCALAR_64 = 3,
	PRESCALAR_256 = 4,
	PRESCALAR_1024 = 5
};


void initRealTimeClock(enum Prescalars prescalar, float periodInSec);
uint8_t getDeltaTime();
bool isTimePast();



#ifdef __cplusplus
}
#endif

#endif