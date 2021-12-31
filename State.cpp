#include <New.h>

#include "State.hpp"
#include "LcdPrintFunctions.hpp"
#include "ProgrammState.hpp"


static char stateStorage[10];


int8_t zeroNegativeBoundaryGreater(int8_t val, int8_t boundary){
	return val > boundary ? boundary : (val < 0 ? 0 : val);
}


//---------------------------InputCallbacks--------------------
void activateAlarm(const Time& t){
	int32_t diff = t.diff(clock.getTime());
	if (diff <= 0){
		diff = abs(diff) + SECONDS_IN_DAY;
	}
	//DEBUG
	Serial.println(diff);
	
	alarmTask.startTimer(diff);
	disableAlarmTask.startTimer(diff + 30);
	state =  new (stateStorage) DefaultState();
}




//--------------------------State------------------------------
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
				state = new(stateStorage) TimeInputState(activateAlarm);
				break;
			case 1:
				lcd.backlight();
				disableBackLightTask.startTimer(5);
				break;
		}
	}
}

//-------------------------InputState----------------------------
template<typename T>
InputState<T>::InputState(void (*consumer)(const T& val))
	: consumer(consumer)
{
	displayTask.disable();
	lcd.clear();
	lcd.cursor_on();
}

template<typename T>
void InputState<T>::handleInput(const ButtonEvent& event){
	if (event.buttonIndex == 0 && event.holdMs >= 1000){
		consumer(m_val);
		return;
	}
	int16_t change = getChange(event);
	moveCursor(event);
	applyChange(change, cursorPosition);
	if (!validateInput()){
		applyChange(-change, cursorPosition);
	}
	lcdShowInput();
}

template<typename T>
void InputState<T>::moveCursor(const ButtonEvent& event){
	if (event.buttonIndex == 2){
		//left
		cursorPosition--;
	}else if (event.buttonIndex == 3){
		//right
		cursorPosition++;
	}
	validateCursor();
}

template<typename T>
void InputState<T>::validateCursor(){
	if (cursorPosition < 0){
		cursorPosition = 0;
	}else if(cursorPosition > maxCursorPosition()){
		cursorPosition = maxCursorPosition();
	}
}


//-----------------------TimeInputState--------------------------
TimeInputState::TimeInputState(void (*consumer)(const Time& t))
	: InputState<Time>(consumer)
{
	//read previous value from eeprom
	lcdShowInput();
}

int16_t TimeInputState::getChange(const ButtonEvent& event) const{
	int16_t result = 0;
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

void TimeInputState::applyChange(int16_t change, int8_t cursorPosition){
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

void TimeInputState::lcdShowInput() const {
	lcd.setCursor(0, 0);
	displayTime(m_val, true);
	uint8_t cursorAt = cursorPosition;
	if (cursorPosition > 1){
		cursorAt++;
	}
	if (cursorPosition > 3){
		cursorAt++;
	}
	lcd.setCursor(cursorAt, 0);
}

//----------------------DateInputState------------------------









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