#include "State.hpp"
#include "LcdPrintFunctions.hpp"
#include "ProgrammState.hpp"


CursorInputState::CursorInputState(){
	displayTask.disable();
	lcd.clear();
}

void CursorInputState::handleInput(const ButtonEvent& event){
	moveCursor(event);
	validateCursor();
}

void CursorInputState::moveCursor(const ButtonEvent& event){
	if (event.buttonIndex == 2){
		//left
		cursorPosition--;
	}else if (event.buttonIndex == 3){
		//right
		cursorPosition++;
	}
	validateCursor();
}

void CursorInputState::validateCursor(){
	if (cursorPosition < 0){
		cursorPosition = maxCursorPosition();
	}else if(cursorPosition > maxCursorPosition()){
		cursorPosition = 0;
	}
}