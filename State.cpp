#include <New.h>

#include "State.hpp"
#include "LcdPrintFunctions.hpp"
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
	lcd.cursor_off();
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
}


//-----------------------InputState----------------------------
InputState::InputState(){
	//read previous value from eeprom
	
	displayTask.disable();
	
	lcd.clear();
	lcdShowInput();
	lcd.cursor_on();
}

void InputState::handleInput(const ButtonEvent& event){
	int8_t change = 0;
	switch (event.buttonIndex){
		case 0:
			//set alarm
			if (event.holdMs >= 1000){
				
				Clock result = Clock(clock);
				result.setTime(m_time);
				if (result <= clock){
					result.incrementDay();
				}

				int32_t deltaSec = result.diff(clock);
				Serial.println(deltaSec);
				alarmTask.startTimer(deltaSec);
				disableAlarmTask.startTimer(deltaSec + 10);
				state =  new (stateStorage) DefaultState();
			}else{
				//up
				change = cursorPosition % 2 == 0 ? 10 : 1;
			}
			break;
		case 1:
			//down
			change = cursorPosition % 2 == 0 ? -10 : -1;
			break;
		case 2:
			//left
			cursorPosition--;
			break;
		case 3:
			//right
			cursorPosition++;
			break;
	}
	cursorPosition = cursorPosition < 0 ? 0 : 
			(cursorPosition > 5 ? 5 : cursorPosition);
	incrementTimeAtCursor(change);
	if (!validateInput()){
		incrementTimeAtCursor(-change);
	}
	lcdShowInput();
}

bool InputState::validateInput(){
	if (m_time.hours < 0 || m_time.minutes < 0 || m_time.seconds < 0){
		return false;
	}
	if (m_time.hours > 23 || m_time.minutes > 59 || m_time.seconds > 59){
		return false;
	}
	return true;
}

void InputState::incrementTimeAtCursor(int8_t change){
	switch(cursorPosition){
		case 0: case 1:
			m_time.hours += change;
			break;
		case 2: case 3:
			m_time.minutes += change;
			break;
		case 4: case 5:
			m_time.seconds += change;
			break;
	}
}

void InputState::lcdShowInput(){
	lcd.setCursor(0, 0);
	displayTime(m_time, true);
	uint8_t cursorAt = cursorPosition;
	if (cursorPosition > 1){
		cursorAt++;
	}
	if (cursorPosition > 3){
		cursorAt++;
	}
	lcd.setCursor(cursorAt, 0);
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
