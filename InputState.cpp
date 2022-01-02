#include "State.hpp"
#include "LcdPrintFunctions.hpp"
#include "ProgrammState.hpp"


template<typename T>
InputState<T>::InputState(void (*consumer)(const T& val))
	: consumer(consumer)
{
	lcd.cursor_on();
}

template<typename T>
void InputState<T>::handleInput(const ButtonEvent& event){
	CursorInputState::handleInput(event);
	
	if (event.buttonIndex == 0 && event.holdMs >= 1000){
		consumer(m_val);
		return;
	}
	int16_t change = getChange(event);
	applyChange(change, cursorPosition);
	if (!validateInput()){
		applyChange(-change, cursorPosition);
	}
	lcdShowInput();
}