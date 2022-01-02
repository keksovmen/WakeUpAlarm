#ifndef LCD_PRINT_FUCTIONS_H
#define LCD_PRINT_FUCTIONS_H

// #include <LiquidCrystal_I2C.h>
// #include "ProgrammState.hpp"
#include <stdint.h>
#include "Clock.hpp"

//In cursor position, of form HH:MM[:SS]
void displayTime(const Time& time, bool enableSecunds=false);

//In cursor position, of form dd:mm:yyyy
void displayDate(const Date& date);

//First row is time HH:MM, second row is date dd.mm.yyyy
void displayDateTime(const Clock& clk);

/**
	@param val can be negative
	@param length tells how much symbols to dysplay
**/
void printZeroPaddedInt(int32_t val, int8_t length);

#endif