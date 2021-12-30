#include <New.h>

#include "State.hpp"
#include "LcdPrintFunctions.hpp"
// #include "Clock.hpp"
#include "ProgrammState.hpp"


static char stateStorage[10];


int8_t zeroNegativeBoundaryGreater(int8_t val, int8_t boundary){
	return val > boundary ? boundary : (val < 0 ? 0 : val);
}


State* State::getDefaultState(){
	return new(stateStorage) DefaultState();
}

State* State::getAlarmState(){
	return new(stateStorage) AlarmState();
}

//-----------------------DefaultState--------------------------
DefaultState::DefaultState(){
	displayTask.startTimer(0);
}


void DefaultState::handleInput(const ButtonEvent& event){
	if (event.holdMs >= 1000){
		switch(event.buttonIndex){
			case 0:
				state = new(stateStorage) InputState();
				break;
			case 1:
				lcd.backlight();
				disableBackLightTask.startTimer(5);
				break;
		}
	}
	// return this;
}


//-----------------------InputState----------------------------
InputState::InputState(){
	//read previous value from eeprom
	
	displayTask.disable();
	
	lcd.clear();
	lcdDisplayInput();
	lcd.cursor_on();
}

void InputState::handleInput(const ButtonEvent& event){
	switch (event.buttonIndex){
		case 0:
			//set alarm
			if (event.holdMs >= 1000){
				
				Clock result = Clock(clock);
				result.setTime(cursorInputToTime());
				if (result <= clock){
					result.incrementDay();
				}

				int32_t deltaSec = result.diff(clock);
				Serial.println(deltaSec);
				alarmTask.startTimer(deltaSec);
				disableAlarmTask.startTimer(deltaSec + 10);
				lcd.cursor_off();
				state =  new (stateStorage) DefaultState();
			}else{
				//up
				cursorInput[cursorPosition]++;
			}
			break;
		case 1:
			//down
			cursorInput[cursorPosition]--;
			break;
		case 2:
			//left
			cursorPosition--;
			if (cursorPosition < 0){
				cursorPosition = 0;
			}
			break;
		case 3:
			//right
			cursorPosition++;
			if (cursorPosition > 3){
				cursorPosition = 3;
			}
			break;
	}
	validateCursorInput();
	lcdDisplayInput();
	
	// return this;
}

void InputState::validateCursorInput(){
	cursorInput[0] = zeroNegativeBoundaryGreater(cursorInput[0], 2);
	if (cursorInput[0] == 2){
		cursorInput[1] = zeroNegativeBoundaryGreater(cursorInput[1], 3);
	}else{
		cursorInput[1] = zeroNegativeBoundaryGreater(cursorInput[1], 9);
	}
	cursorInput[2] = zeroNegativeBoundaryGreater(cursorInput[2], 5);
	cursorInput[3] = zeroNegativeBoundaryGreater(cursorInput[3], 9);
}

Time InputState::cursorInputToTime(){
	return Time(0, 
				cursorInput[2] * 10 + cursorInput[3],
				cursorInput[0] * 10 + cursorInput[1]);
}

void InputState::lcdDisplayInput(){
	lcd.setCursor(0, 0);
	displayTime(cursorInputToTime());
	lcd.setCursor(
		cursorPosition > 1 ? cursorPosition + 1 : cursorPosition,
		0);
}

//----------------------AlarmState----------------------------
AlarmState::AlarmState(){
	digitalWrite(ALARM_OUT, HIGH);
}

void AlarmState::handleInput(const ButtonEvent& event){
	if (event.holdMs >= 1000){
		digitalWrite(ALARM_OUT, LOW);
		disableAlarmTask.disable();
		state = new (stateStorage)DefaultState();
	}
}
