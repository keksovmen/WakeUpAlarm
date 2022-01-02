#include "LcdPrintFunctions.hpp"
#include "ProgrammState.hpp"
#include "Util.hpp"

char intToAscii(int8_t digit){
	return char(48 + digit);
}

void displayTime(const Time& time, bool enableSecunds){
	printZeroPaddedInt(time.hours, 2);
	lcd.print(':');
	printZeroPaddedInt(time.minutes, 2);
	if (enableSecunds){
		lcd.print(':');
		printZeroPaddedInt(time.seconds, 2);
	}
}

void displayDate(const Date& date){
	printZeroPaddedInt(date.day, 2);
	lcd.print('.');
	printZeroPaddedInt(date.day, 2);
	lcd.print('.');
	printZeroPaddedInt(date.year, 4);
}

void displayDateTime(const Clock& clk){
	lcd.home();
	displayTime(clk.getTime(), true);
	lcd.setCursor(0, 1);
	displayDate(clk.getDate());
}

void printZeroPaddedInt(int32_t val, int8_t totalSymbols){
	char buffer[12];
	int32_t divider = pow10(totalSymbols);
	int offset = 0;
	if (val < 0){
		buffer[0] = '-';
		offset = 1;
		val = -val;
	}
	
	for (int i = 0; i < totalSymbols; i++){
		int8_t tmp = val / divider;
		val -= tmp * divider;
		buffer[offset + i] = intToAscii(tmp);
		divider /= 10;
	}
	buffer[totalSymbols + offset] = '\0';
	
	lcd.print(buffer);
}
