#ifndef CLOCK_H
#define CLOCK_H
#include <stdint.h>

#define STARTING_YEAR 1970
#define SECONDS_IN_DAY 86400L

class Time{
	public:
		/**
			@param seconds - in range [0 - 59]
			@param minutes - in range [0 - 59]
			@param hours - in range [0 - 23]
		**/
		int8_t seconds;
		int8_t minutes;
		int8_t hours;
		
		
		Time(int8_t seconds=0,
				int8_t minutes=0,
				int8_t hours=0) : 
					seconds(seconds),
					minutes(minutes),
					hours(hours){};
		Time (const Time& d) = default;
		Time& operator= (const Time& d) = default;
		
		Time operator-(const Time& t) const;
	
		bool addSecond();
		
		int32_t toSeconds() const;
		int32_t diff(const Time& t) const;
		
	private:
		bool addMinute();
		bool addHour();
};


class Date{
	public:
		/**
			@param day - in range [0 - 31]
			@param month - in range [1 - 12]
			@param year - in range [STARTING_YEAR - 9999]
			@param currentDay - amount of days since STARTING_YEAR
		**/
		int8_t day;
		int8_t month;
		int16_t year;
		int32_t currentDay = 0;
		
		Date(int8_t day=1, 
				int8_t month=1,
				int16_t year=STARTING_YEAR);
		Date (const Date& d) = default;
		Date& operator= (const Date& d) = default;
		// Date operator-(const Date& t) const;
		
		void addDay();
		
		int32_t diff(const Date& d) const;
	private:
		void addMonth();
		void addYear();
};


class Clock{
	public:
		Clock(){};
		Clock(const Time& time,
				const Date& date) : time(time), date(date){};
		Clock(const Clock& clk) = default;
		
		// bool operator< (const Cloc& l, const Clock& r);
		bool operator<= (const Clock& v);
		
		void incrementSecond();
		void incrementDay();

		int32_t diff(const Clock& clk) const;
		
		const Time& getTime()const {return time;}
		const Date& getDate()const {return date;}
		
		void setTime(const Time& t){this->time = t;};
		void setDate(const Date& d){this->date = d;};

		
	private:
		Time time;
		Date date;
};

#endif