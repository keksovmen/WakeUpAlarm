#ifndef STATE_H
#define STATE_H


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
		bool validateInput();
		void incrementTimeAtCursor(int8_t change);
		void lcdShowInput();
		
		int8_t cursorPosition = 0;
		Time m_time;
		// int8_t hours = 0;
		// int8_t minutes = 0;
		// int8_t seconds = 0;
};

class AlarmState : public State{
	public:
		AlarmState();
		void handleInput(const ButtonEvent& event) override;
};



#endif