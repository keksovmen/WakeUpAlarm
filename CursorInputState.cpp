#include "State.hpp"
#include "LcdPrintFunctions.hpp"
#include "Globals.hpp"


CursorInputState::CursorInputState(){
}

void CursorInputState::handleEvent(const ButtonEvent& event){
	if (isCancelEvent(event)){
		setState(StateFactory::createDefaultState());
		//TODO: this method called as parent from children
		//do something to prevent crushes when state changes
		return;
	}
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