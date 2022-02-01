#include <EEPROM.h>
#include "ProgrammState.hpp"
#include "LcdPrintFunctions.hpp"
#include "EepromPositions.h"


static bool output = false;

void diodRoutine(){
	digitalWrite(DIOD_BLINK_PIN, output);
	output = !output;
	diodTask.startTimer(1);
}

void displayRoutine(){
	printHomePage();
	displayTask.startTimer(1);
}

void autoSaveDateRoutine(){
	EEPROM.put(DATE_ADDRESS, clock.getDate());
	Clock tmp;
	tmp.setDate(clock.getDate());
	tmp.incrementDay();
	dateAutoSaveTask.startTimer(tmp.diff(clock));
}