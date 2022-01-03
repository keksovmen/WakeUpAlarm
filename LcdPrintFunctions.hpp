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

//Prints date time from global clock, and A12 for active alarms
void printHomePage(bool clear=false);

/**
	@param val can be negative
	@param totalSymbols tells how much symbols to display
**/
void printZeroPaddedInt(int32_t val, int8_t totalSymbols);

#endif