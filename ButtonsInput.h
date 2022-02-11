#ifndef BUTTONS_INPUT_H
#define BUTTONS_INPUT_H

#include <stdint.h>

/**
	Will use PCINT2 on 4,5,6,7 uno pins,
	Pins connected to buttons and then to ground
**/


#ifdef __cplusplus
extern "C" {
#endif

void initInputButtons(void (*buttonConsumer)(int8_t));

#ifdef __cplusplus
}
#endif

#endif