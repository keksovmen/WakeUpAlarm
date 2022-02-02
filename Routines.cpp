#include "ProgrammState.hpp"
#include "LcdPrintFunctions.hpp"
#include "EepromPositions.h"


static bool output = false;

void diodRoutine(){
	digitalWrite(DIOD_BLINK_PIN, output);
	output = !output;
	diodTask.startTimer(1);
}
