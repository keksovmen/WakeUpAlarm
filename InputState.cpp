#include "State.hpp"
#include "LcdPrintFunctions.hpp"
#include "ProgrammState.hpp"


template<typename T>
InputState<T>::InputState(void (*consumer)(const T& val),
							const T& initialValue)
	: m_val(initialValue), consumer(consumer)
{
	lcd.cursor_on();
}

template<typename T>
void InputState<T>::handleEvent(const ButtonEvent& event){
	CursorInputState::handleEvent(event);
	if (isCancelEvent(event)){
		// setState(StateFactory::createDefaultState());
		return;
	}
	if (isAcceptEvent(event)){
		consumer(m_val);
		return;
	}
	int32_t change = getChange(event);
	applyChange(change, cursorPosition);
	if (!validateInput()){
		applyChange(-change, cursorPosition);
	}
	printOnDisplay();
}