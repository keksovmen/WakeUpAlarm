// #include <New.h>

// #include "State.hpp"
// #include "LcdPrintFunctions.hpp"
// #include "ProgrammState.hpp"
// #include "Settings.hpp"
// #include "Util.hpp"


// static char stateStorage[13];


// int8_t zeroNegativeBoundaryGreater(int8_t val, int8_t boundary){
	// return val > boundary ? boundary : (val < 0 ? 0 : val);
// }


//---------------------------InputCallbacks--------------------
// void activateAlarm(const Time& t){
	// int32_t diff = t.diff(clock.getTime());
	// if (diff <= 0){
		// diff = abs(diff) + SECONDS_IN_DAY;
	// }
	//DEBUG
	// Serial.println(diff);
	
	// alarmTask.startTimer(diff);
	// disableAlarmTask.startTimer(diff + 30);
	// state =  new (stateStorage) DefaultState();
// }

// void setDate(const Date& d){
	// clock.setDate(d);
	//DEBUG
	// Serial.print("Current day ");
	// Serial.println(clock.getDate().currentDay);
	
	// state =  new (stateStorage) DefaultState();
// }

// void setTime(const Time& t){
	// clock.setTime(t);
	// state =  new (stateStorage) DefaultState();
// }

// void printInt(const int16_t& val){
	// Serial.println(val);
	// state =  new (stateStorage) DefaultState();
// }


