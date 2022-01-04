#include "ProgrammState.hpp"
#include "LcdPrintFunctions.hpp"


static bool output = false;

void diodRoutine(){
	digitalWrite(RELE_OUT, output);
	output = !output;
	diodTask.startTimer(1);
}

void displayRoutine(){
	printHomePage();
	displayTask.startTimer(1);
}