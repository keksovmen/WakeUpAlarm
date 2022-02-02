#include <EEPROM.h>
#include "EepromClock.hpp"


EepromClock::EepromClock(int dateAddress) :
	Clock(Time(), readDate(dateAddress)),
	dateAddress(dateAddress)
{
}

void EepromClock::incrementSecond(){
	Clock::incrementSecond();
	generateEvent();
}

void EepromClock::incrementDay(){
	Clock::incrementDay();
	saveDate(dateAddress);
}

void EepromClock::setTime(const Time& t){
	Clock::setTime(t);
}

void EepromClock::setDate(const Date& d){
	Clock::setDate(d);
	saveDate(dateAddress);
}

Date EepromClock::readDate(int address){
	Date d;
	EEPROM.get(address, d);
	validateAndFixDate(d);
	return d;
}

void EepromClock::saveDate(int address){
	EEPROM.put(address, getDate());
}