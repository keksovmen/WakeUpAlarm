#include "State.hpp"

void State::actOnEvents(){
	
}

void State::printOnDisplay() const{
	
}

bool State::isCancelEvent(const ButtonEvent& event){
	return event.buttonIndex == 1 && event.holdMs >= 1000;
}

bool State::isAcceptEvent(const ButtonEvent& event){
	return event.buttonIndex == 0 && event.holdMs >= 1000;
}