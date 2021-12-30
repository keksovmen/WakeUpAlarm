#include "LcdPrintFunctions.hpp"
#include "ProgrammState.hpp"

// extern LiquidCrystal_I2C lcd;

char intToAscii(int8_t digit){
	return char(48 + digit);
}

void convertIntToZeroPaded(int8_t val, char buffer[2]){
	uint8_t tens = val / 10;
	uint8_t ones = val - tens * 10;
	buffer[0] = intToAscii(tens);
	buffer[1] = intToAscii(ones);	
}




void displayTime(const Time& time, bool enableSecunds){
	char buffer[3] = {'\0', '\0', '\0'};
	
	convertIntToZeroPaded(time.hours, buffer);
	lcd.print(buffer);
	lcd.print(':');
	
	convertIntToZeroPaded(time.minutes, buffer);
	lcd.print(buffer);
	
	if (enableSecunds){
		lcd.print(':');
		convertIntToZeroPaded(time.seconds, buffer);
		lcd.print(buffer);
	}
}

void displayDate(const Date& date){
	char buffer[3] = {'\0', '\0', '\0'};
	
	convertIntToZeroPaded(date.day, buffer);
	lcd.print(buffer);
	lcd.print('.');
	
	convertIntToZeroPaded(date.month, buffer);
	lcd.print(buffer);
	lcd.print('.');
	
	lcd.print(date.year);
}

void displayDateTime(const Clock& clk){
	lcd.home();
	displayTime(clk.getTime(), true);
	lcd.setCursor(0, 1);
	displayDate(clk.getDate());
}
