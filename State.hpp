#ifndef STATE_H
#define STATE_H


#include "ButtonsControl.hpp"
#include "Clock.hpp"


class State;
class DefaultState;
class TimeInputState;
class DateInputState;
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

template <typename T>
class InputState : public State{
	public:
		InputState(void (*consumer)(const T& val));
		void handleInput(const ButtonEvent& event) override;
	
	protected:
		T m_val;
		
		int16_t getChange(const ButtonEvent& event) const = 0;
		int8_t maxCursorPosition() const = 0;
		void applyChange(int16_t change, int8_t cursorPosition) = 0;
		bool validateInput() = 0;
		void lcdShowInput() = 0;
	
	private:
		int8_t cursorPosition = 0;
		void (*consumer)(const T& val);
		
		void moveCursor(const ButtonEvent& event);
		void validateCursor();
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



// class DateInputState : public InputState<Date>{
	// public:
		// DateInputState(void (*consumer)(const Date& d));
		
		// void handleInput(const ButtonEvent& event) override;
	
	// protected:
		// bool validateInput();
		// void incrementTimeAtCursor(int8_t change);
		// void lcdShowInput();
		
		// void (*consumer)(const Date& d);
		// int8_t cursorPosition = 0;
		// Date m_date;
// };

class AlarmState : public State{
	public:
		AlarmState();
		void handleInput(const ButtonEvent& event) override;
};



#endif