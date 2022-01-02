#include "State.hpp"
#include "LcdPrintFunctions.hpp"
#include "ProgrammState.hpp"
#include "Util.hpp"


IntInputState::IntInputState(void (*consumer)(const int16_t& val),
						const int16_t& initialValue,
						int16_t minVal,
						int16_t maxVal)
	: InputState<int16_t>(consumer, initialValue),
		minVal(minVal), maxVal(maxVal),
		digitsToRepresent(findLongLength(maxVal))
{
	lcdShowInput();
}

int16_t IntInputState::getChange(const ButtonEvent& event) const{
	int16_t result = 0;
	if (event.buttonIndex == 0){
		//up
		result = 1;
	}else if (event.buttonIndex == 1){
		//down
		result = -1;
	}
	return result * pow10(digitsToRepresent - cursorPosition);
}

int8_t IntInputState::maxCursorPosition() const{
	return digitsToRepresent - 1;
}

void IntInputState::applyChange(int16_t change, int8_t cursorPosition){
	m_val += change;
}

bool IntInputState::validateInput() {
	return minVal <= m_val && m_val <= maxVal;
}

void IntInputState::lcdShowInput() const {
	lcd.clear();
	lcd.setCursor(0, 1);
	printZeroPaddedInt(m_val, digitsToRepresent);
	lcd.setCursor(m_val < 0 ? cursorPosition + 1 : cursorPosition,
					1);
}