#include "State.hpp"
#include "LcdPrintFunctions.hpp"
#include "ProgrammState.hpp"


DateInputState::DateInputState(void (*consumer)(const Date& val),
								const Date& initialValue)
	: InputState<Date>(consumer, initialValue)
{
	printOnDisplay();
}

int32_t DateInputState::getChange(const ButtonEvent& event) const{
	int32_t result = 0;
	if(event.buttonIndex == 0){
		//up
		result = 1;
	}else if (event.buttonIndex == 1){
		//down
		result = -1;
	}
	//for day and month
	if (cursorPosition < 4){
		if (cursorPosition % 2 == 0){
			result *= 10;
		}
	}else{
		//for year
		for(int i = 0; i < maxCursorPosition() - cursorPosition; i++){
			result *= 10;
		}
	}
	return result;
}

int8_t DateInputState::maxCursorPosition() const{
	return 7;
}

void DateInputState::applyChange(int32_t change, int8_t cursorPosition){
	switch(cursorPosition){
		case 0: case 1:
			m_val.day += change;
			break;
		case 2: case 3:
			m_val.month += change;
			break;
		case 4: case 5: case 6: case 7:
			m_val.year += change;
			break;
	}
}

bool DateInputState::validateInput() {
	if (m_val.day < 1 || 
			m_val.month < 1 || 
			m_val.year < STARTING_YEAR){
		return false;
	}
	if (m_val.day > daysInMonth(m_val.month, m_val.year) ||
			m_val.month > 12 || 
			m_val.year > MAX_YEAR){
		return false;
	}
	return true;
}

void DateInputState::printOnDisplay() const {
	lcd.setCursor(0, INPUT_ROW_NUMBER);
	displayDate(m_val);
	uint8_t cursorAt = cursorPosition;
	if (cursorPosition > 1){
		cursorAt++;
	}
	if (cursorPosition > 3){
		cursorAt++;
	}
	lcd.setCursor(cursorAt, INPUT_ROW_NUMBER);
}