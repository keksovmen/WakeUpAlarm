#ifndef STATE_H
#define STATE_H


// #include "ProgrammState.hpp"
#include "ButtonsControl.hpp"
#include "Clock.hpp"


class State;
class DefaultState;
class InputState;
class AlarmState;




class State{
	public:
		// virtual ~State() = default;
		virtual void handleInput(const ButtonEvent& event) = 0;
		static State* getDefaultState();
		static State* getAlarmState();
};


class DefaultState : public State{
	public:
		DefaultState();
		
		void handleInput(const ButtonEvent& event) override;
};

class InputState : public State{
	public:
		InputState();
		
		void handleInput(const ButtonEvent& event) override;
	
	protected:
		void validateCursorInput();
		Time cursorInputToTime();
		void lcdDisplayInput();
		
		int8_t cursorPosition = 0;
		int8_t cursorInput[4] = {0, 0, 0, 0};
};

class AlarmState : public State{
	public:
		AlarmState();
		void handleInput(const ButtonEvent& event) override;
};



#endif