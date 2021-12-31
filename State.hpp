#ifndef STATE_H
#define STATE_H


#include "ButtonsControl.hpp"
#include "Clock.hpp"


class State;
class DefaultState;
class TimeInputState;
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

class TimeInputState : public State{
	public:
		TimeInputState(void (*consumer)(const Time& t));
		
		void handleInput(const ButtonEvent& event) override;
	
	protected:
		bool validateInput();
		void incrementTimeAtCursor(int8_t change);
		void lcdShowInput();
		
		void (*consumer)(const Time& t);
		int8_t cursorPosition = 0;
		Time m_time;
};

class AlarmState : public State{
	public:
		AlarmState();
		void handleInput(const ButtonEvent& event) override;
};



#endif