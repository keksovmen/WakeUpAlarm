#include "Clock.hpp"


// bool isOverflow(int16_t val, int16_t boundary){
	// return val >= boundary;
// }

bool isLeapYear(int16_t year){
	return ((year % 400 == 0) || 
		((year % 4 == 0) && (year % 100 != 0)));
}


/**
	@param month [0 - 11]
**/

int8_t daysInMonth(int8_t month, int16_t year){
	int8_t daysInMonth[12]{31,		//January
							28, 	//February, needs checks
							31,		//March
							30,		//April
							31,		//May
							30,		//June
							31,		//July
							31,		//August
							30,		//September
							31,		//October
							30,		//November
							31};		//December
	if (month != 1){
		return daysInMonth[month];
	}
	
	if (isLeapYear(year)){
		return 29;
	}else{
		return 28;
	}
}




//-----------------------Time------------------------------
Time Time::operator-(const Time& t) const {
	return Time(seconds - t.seconds,
				minutes - t.minutes,
				hours - t.hours);
}

bool Time::addSecond(){
	seconds++;
	if(seconds >= 60){
		seconds = 0;
		return addMinute();
	}
	return false;
}

bool Time::addMinute(){
	minutes++;
	if (minutes >= 60){
		minutes = 0;
		return addHour();
	}
	return false;
}

bool Time::addHour(){
	hours++;
	if (hours >= 24){
		hours = 0;
		return true;
	}
	return false;
}

int32_t Time::toSeconds() const{
	return hours * 3600L + minutes * 60 + seconds;
}

int32_t Time::diff(const Time& t) const{
	return ((*this) - t).toSeconds();
}


//-----------------------Date------------------------------
Date::Date(int8_t day, 
		int8_t month,
		int16_t year) : 
	day(day), month(month), year(year)
{
	for (int i = STARTING_YEAR; i < year; i++){
		if(isLeapYear(i)){
			currentDay += 366;
		}else{
			currentDay += 365;
		}
	}
	for (int i = 0; i < month - 1; i++){
		currentDay += daysInMonth(i, year);
	}
	currentDay += day;
}

void Date::addDay(){
	day++;
	currentDay++;
	if ((day - 1) >= daysInMonth(month - 1, year)){
		day = 1;
		addMonth();
	}
	
}

void Date::addMonth(){
	month++;
	if ((month - 1) >= 12){
		month = 1;
		addYear();
	}
}

void Date::addYear(){
	year++;
	if (year > 9999){
		year = STARTING_YEAR;
	}
}

int32_t Date::diff(const Date& d) const{
	return (currentDay - d.currentDay) * SECONDS_IN_DAY;
}

//-----------------------Clock-----------------------------

bool Clock::operator<= (const Clock& v){
	return diff(v) <= 0;
}

void Clock::incrementSecond(){
	if (time.addSecond()){
		date.addDay();
	}
}

void Clock::incrementDay(){
	date.addDay();
}

int32_t Clock::diff(const Clock& clk) const{
	return date.diff(clk.date) + time.diff(clk.time);
}