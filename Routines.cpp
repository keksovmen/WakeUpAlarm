#include "ProgrammState.hpp"
#include "LcdPrintFunctions.hpp"


static bool output = false;

void diodRoutine(){
	digitalWrite(RELE_OUT, output);
	output = !output;
	diodTask.startTimer(1);
}

void timeRoutine(){
	clock.incrementSecond();
	clockTask.startTimer(1);
}

void displayRoutine(){
	printHomePage();
	displayTask.startTimer(1);
}

void backlightRoutine(){
	lcd.noBacklight();
}


void disableAlarmRoutine(){
	//state must be alarm otherwise won't work
	//by logic it will be alarm, because when you entered
	//alarm state you can only change it to default
	//and when you changing you disable this routine
	getState()->handleInput(ButtonEvent(0, 1000));
}