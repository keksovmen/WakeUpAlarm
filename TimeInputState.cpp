#include "State.hpp"
#include "LcdPrintFunctions.hpp"
#include "Globals.hpp"


TimeInputState::TimeInputState(void (*consumer)(const Time& t),
								const Time& initialValue)
	: InputState<Time>(consumer, initialValue)
{
	printOnDisplay();
}

int32_t TimeInputState::getChange(const ButtonEvent& event) const{
	int32_t result = 0;
	if(event.buttonIndex == 0){
		//up
		result = 1;
	}else if (event.buttonIndex == 1){
		//down
		result = -1;
	}
	if (cursorPosition % 2 == 0){
		result *= 10;
	}
	return result;
}

int8_t TimeInputState::maxCursorPosition() const{
	return 5;
}

void TimeInputState::applyChange(int32_t change, int8_t cursorPosition){
	switch(cursorPosition){
		case 0: case 1:
			m_val.hours += change;
			break;
		case 2: case 3:
			m_val.minutes += change;
			break;
		case 4: case 5:
			m_val.seconds += change;
			break;
	}
}

bool TimeInputState::validateInput() {
	if (m_val.hours < 0 || m_val.minutes < 0 || m_val.seconds < 0){
		return false;
	}
	if (m_val.hours > 23 || m_val.minutes > 59 || m_val.seconds > 59){
		return false;
	}
	return true;
}

void TimeInputState::printOnDisplay() const {
	lcd.setCursor(0, INPUT_ROW_NUMBER);
	displayTime(m_val, true);
	uint8_t cursorAt = cursorPosition;
	if (cursorPosition > 1){
		cursorAt++;
	}
	if (cursorPosition > 3){
		cursorAt++;
	}
	lcd.setCursor(cursorAt, INPUT_ROW_NUMBER);
}