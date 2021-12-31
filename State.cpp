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


//-----------------------TimeInputState----------------------------
TimeInputState::TimeInputState(void (*consumer)(const Time& t))
	: consumer(consumer)
{
	//read previous value from eeprom
	
	displayTask.disable();
	
	lcd.clear();
	lcdShowInput();
	lcd.cursor_on();
}

void TimeInputState::handleInput(const ButtonEvent& event){
	int8_t change = 0;
	switch (event.buttonIndex){
		case 0:
			//set alarm
			if (event.holdMs >= 1000){
				consumer(m_time);
				return;
			}
			//up
			change = cursorPosition % 2 == 0 ? 10 : 1;
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

bool TimeInputState::validateInput(){
	if (m_time.hours < 0 || m_time.minutes < 0 || m_time.seconds < 0){
		return false;
	}
	if (m_time.hours > 23 || m_time.minutes > 59 || m_time.seconds > 59){
		return false;
	}
	return true;
}

void TimeInputState::incrementTimeAtCursor(int8_t change){
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

void TimeInputState::lcdShowInput(){
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
