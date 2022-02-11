#include "LcdPrintFunctions.hpp"
#include "Globals.hpp"
#include "Util.hpp"


static void printActiveAlarms(){
	const int8_t beginning = 15 - (TOTAL_ALARMS - 1);
	lcd.setCursor(beginning - 1, 1);
	if (alarms.isAnyActivated()){
		lcd.print("A");
		for (int8_t i = 0; i < TOTAL_ALARMS; i ++){
			if (alarms.isAlarmActivated(i)){
				lcd.print(i + 1);
			}else{
				lcd.print(" ");
			}
		}
	}else{
		for (int8_t i = 0; i < TOTAL_ALARMS + 1; i++){
			lcd.print(" ");
		}
	}
}

static void printTemperatureTopRight(float temp){
	const int BEGINING = 10;
	lcd.setCursor(BEGINING, 0);
	int8_t totalLength = 3 + findLongLength(temp);
	if (temp < 0){
		totalLength++;
	}
	printTemperature(temp);
	for (int i = totalLength + BEGINING; i < LCD_TOTAL_COLUMNS; i++){
		lcd.print(" ");
	}
}



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
	printZeroPaddedInt(date.month, 2);
	lcd.print('.');
	printZeroPaddedInt(date.year, 4);
}

void displayDateTime(const Clock& clk){
	lcd.home();
	displayTime(clk.getTime(), true);
	lcd.setCursor(0, 1);
	displayDate(clk.getDate());
}

void printHomePage(const Clock& clk, bool clear){
	if (clear){
		lcd.clear();
	}
	displayDateTime(clk);
	printActiveAlarms();
	printTemperatureTopRight(tempHandler.getTemperature());
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

//if previously had minus sign, clear last digit of it
void printZeroPaddedIntClearRight(int32_t val, int8_t totalSymbols){
	printZeroPaddedInt(val, totalSymbols);
	lcd.print(' ');
}

void printTemperature(float temp){
	lcd.print(temp, 2);
	lcd.print('C');
}
