#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

//Will calculate length of character sequence to represent value
//Negative sine doesn't count
int8_t findLongLength(int32_t val);

int32_t pow10(int8_t power);
#endif