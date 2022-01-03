#ifndef ARDUINO
#include <iostream>
// #include "Task.hpp"
// #include "Clock.hpp"
#include "Util.hpp"


void say(){
	std::cout << "LOH" << std::endl;
}

// void printClock(const Clock& clk){
	// std::cout << int(clk.getTime().hours) << ":"
		// << int(clk.getTime().minutes) << ":"
		// << int(clk.getTime().seconds) << " "
		// << int(clk.getDate().day) << "."
		// << int(clk.getDate().month) << "."
		// << int(clk.getDate().year) << std::endl;
// }

// void printTime(const Time& t){
	// std::cout << int(t.hours) << ":"
		// << int(t.minutes) << ":"
		// << int(t.seconds) << std::endl;
// }

// void printDate(const Date& d){
	// std::cout << int(d.day) << "."
			// << int(d.month) << "."
			// << int(d.year) << "."
			// << int(d.currentDay) << std::endl;
// }

int main(){
	// Task t(say);
	// t.startTimer(25);
	// std::cout << t.isActivated() << std::endl;
	// t.consumeTime(20);
	// std::cout << t.isActivated() << std::endl;
	// Clock first;
	// Clock first({0, 0, 8}, {29, 12, 2021});
	// printClock(first);
	// first.setTime({0,0,10});
	// printClock(first);
	
	// Clock second(first);
	// second.setTime({0, 0, 8});
	// printClock(first);
	// printClock(second);
	// printTime(second.getTime());
	// std::cout << first.diff(second) << std::endl;
	// second.setHours(7);
	// second.incrementDay();
	// std::cout << second.diff(first) << std::endl;
	// std::cout << (first < second) << std::endl;
	
	// Time t1(0, 0, 12);
	// Time t2(0, 0, 13);
	// printTime(t1 - t2);
	// std::cout << t1.diff(t2) << std::endl;
	// Date d1;
	// Date d2;
	// d2.addDay();
	// d1.addYear();
	// printDate(d1.diff(d2));
	// std::cout << d1.diff(d2) << std::endl;
	// std::cout << int(pow10(3)) << std::endl;
	std::cout << int(findLongLength(2)) << std::endl;
	std::cout << int(findLongLength(30)) << std::endl;
	std::cout << int(findLongLength(400)) << std::endl;
	std::cout << int(findLongLength(5000)) << std::endl;
	std::cout << int(findLongLength(60000)) << std::endl;
	std::cout << int(findLongLength(600000)) << std::endl;
	std::cout << int(findLongLength(6000000)) << std::endl;
}

#endif
