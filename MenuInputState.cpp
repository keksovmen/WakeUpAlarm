#include <avr/pgmspace.h>
#include "State.hpp"
#include "LcdPrintFunctions.hpp"
#include "Globals.hpp"
#include "Util.hpp"



#define ALARMS_MENUS_OFFSET 7


//remember current lcd has 16 symbols on the line
static const char s0[] PROGMEM = "Set time";
static const char s1[] PROGMEM = "Set date";
static const char s2[] PROGMEM = "Set backlight";
static const char s3[] PROGMEM = "Set off period";
static const char s4[] PROGMEM = "Set temp period";
static const char s5[] PROGMEM = "Set audio delay";
static const char s6[] PROGMEM = "Add sec in mins";
static const char s7[] PROGMEM = "Set alarm time ";

static PGM_P const MENUS[] PROGMEM = {s0, s1, s2, s3, s4, s5, s6, s7};


//cursed but does the job
static uint8_t selectedAlarmId = 0;


void setTime(const Time& t){
	clock.setTime(t);
	alarms.updateAlarmTimers();
	setState(StateFactory::createDefaultState());
}

void setDate(const Date& d){
	clock.setDate(d);
	// DEBUG
	Serial.print("Current day ");
	Serial.println(clock.getDate().currentDay);
	
	setState(StateFactory::createDefaultState());
}

void setSelectedAlarmTime(const Time& t){
	alarms.setAlarmTime(t, selectedAlarmId);
	setState(StateFactory::createDefaultState());
}

void setBackLight(const int32_t& s){
	lcdLightHandler.setBackLightDuration(s);
	setState(StateFactory::createDefaultState());
}

void setAlarmOffAfter(const int32_t& s){
	alarms.setAlarmOffAfter(s);
	setState(StateFactory::createDefaultState());
}

void setTemperatureRefreshPeriod(const int32_t& s){
	tempHandler.setTemperaturePeriod(s);
	setState(StateFactory::createDefaultState());
}

void setAudioDelay(const int32_t& s){
	alarms.setAudioDelay(s);
	setState(StateFactory::createDefaultState());
}

void setAddSecund(const int32_t& s){
	additionalTime.setPeriod(s);
	setState(StateFactory::createDefaultState());
}


MenuInputState::MenuInputState(){
	printOnDisplay();
}

void MenuInputState::handleEvent(const ButtonEvent& event){
	CursorInputState::handleEvent(event);
	if (isCancelEvent(event)){
		// setState(StateFactory::createDefaultState());
		return;
	}
	if (event.buttonIndex == 0){
		//select
		switch(cursorPosition){
			case 0:
				setState(StateFactory::createInputTimeState(
							setTime,
							clock.getTime()));
				return;
			case 1:
				setState(StateFactory::createInputDateState(
							setDate,
							clock.getDate()));
				return;
			case 2:
				setState(StateFactory::createInputIntState(
							setBackLight,
							MIN_BACK_LIGHT_DURATION,
							MAX_BACK_LIGHT_DURATION,
							lcdLightHandler.getBackLightDuration()));
				return;
			case 3:
				setState(StateFactory::createInputIntState(
							setAlarmOffAfter,
							MIN_AUTO_OFF_PERIOD,
							MAX_AUTO_OFF_PERIOD,
							alarms.getAlarmOffAfter()));
				return;
			case 4:
				setState(StateFactory::createInputIntState(
							setTemperatureRefreshPeriod,
							MIN_TEMPERATURE_PERIOD,
							MAX_TEMPERATURE_PERIOD,
							tempHandler.getTemperaturePeriod()));
				return;
			case 5:
				setState(StateFactory::createInputIntState(
							setAudioDelay,
							MIN_AUDIO_DELAY,
							MAX_AUDIO_DELAY,
							alarms.getAudioDelay()));
				return;
			case 6:
				setState(StateFactory::createInputIntState(
							setAddSecund,
							MIN_ADDITIONAL_TIME_PERIOD,
							MAX_ADDITIONAL_TIME_PERIOD,
							additionalTime.getPeriod()));
				return;
			default:	//for alarms settings
				selectedAlarmId = cursorPosition - ALARMS_MENUS_OFFSET;
				setState(StateFactory::createInputTimeState(
						setSelectedAlarmTime,
						alarms.getAlarmTime(selectedAlarmId)));
				return;
		}
	}
	printOnDisplay();
}

int8_t MenuInputState::maxCursorPosition() const {
	return ALARMS_MENUS_OFFSET - 1 + TOTAL_ALARMS;
}


void MenuInputState::printOnDisplay() const {
	char buffer[17];
	const uint8_t menuIndex = cursorPosition < ALARMS_MENUS_OFFSET ?
							cursorPosition : ALARMS_MENUS_OFFSET;
	strcpy_P(buffer, (PGM_P)pgm_read_word(&MENUS[menuIndex]));
	lcd.clear();
	lcd.print(buffer);
	//alarm number
	if (cursorPosition >= ALARMS_MENUS_OFFSET){
		lcd.print(cursorPosition - (ALARMS_MENUS_OFFSET - 1));
	}
	lcd.setCursor(0, 1);
	switch(cursorPosition){
		case 0:
			displayTime(clock.getTime(), true);
			break;
		case 1:
			displayDate(clock.getDate());
			break;
		case 2:
			printZeroPaddedInt(lcdLightHandler.getBackLightDuration(),
								findLongLength(MAX_BACK_LIGHT_DURATION));
			break;
		case 3:
			printZeroPaddedInt(alarms.getAlarmOffAfter(),
								findLongLength(MAX_AUTO_OFF_PERIOD));
			break;
		case 4:
			printZeroPaddedInt(tempHandler.getTemperaturePeriod(),
								findLongLength(MAX_TEMPERATURE_PERIOD));
			break;
		case 5:
			printZeroPaddedInt(alarms.getAudioDelay(),
								findLongLength(MAX_AUDIO_DELAY - MIN_AUDIO_DELAY));
			break;
		case 6:
			printZeroPaddedInt(additionalTime.getPeriod(),
								findLongLength(MAX_ADDITIONAL_TIME_PERIOD - MIN_ADDITIONAL_TIME_PERIOD));
			break;
		default:
			displayTime(alarms.getAlarmTime(cursorPosition - ALARMS_MENUS_OFFSET), true);
			break;
	}
}