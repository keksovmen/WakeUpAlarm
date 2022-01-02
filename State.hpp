#ifndef STATE_H
#define STATE_H


#include "ButtonsControl.hpp"
#include "Clock.hpp"


class State;
class DefaultState;
class CursorInputState;
class MenuInputState;

template<typename T>
class InputState;
class TimeInputState;
class DateInputState;
class IntInputState;
class AlarmState;

class StateFactory;



class State{
	public:
		// virtual ~State() = default;
		virtual void handleInput(const ButtonEvent& event) = 0;
};


class DefaultState : public State{
	public:
		DefaultState();
		
		void handleInput(const ButtonEvent& event) override;
};

class CursorInputState : public State{
	public:
		CursorInputState();
		virtual void handleInput(const ButtonEvent& event) override;
		
	protected:
		int8_t cursorPosition = 0;
		
		virtual int8_t maxCursorPosition() const = 0;
		//ideal to call in constructor but doesn't work
		//https://stackoverflow.com/questions/962132/calling-virtual-functions-inside-constructors
		//be sure to call in children constructor
		virtual void lcdShowInput() const = 0;
		
	private:
		void moveCursor(const ButtonEvent& event);
		void validateCursor();
		
};

class MenuInputState : public CursorInputState{
	public:
		MenuInputState();
		void handleInput(const ButtonEvent& event) override;
	protected:
		int8_t maxCursorPosition() const override;
		void lcdShowInput() const override;
};


template <typename T>
class InputState : public CursorInputState{
	public:
		InputState(void (*consumer)(const T& val));
		void handleInput(const ButtonEvent& event) override;
	
	protected:
		T m_val;
		
		virtual int16_t getChange(const ButtonEvent& event) const = 0;
		virtual void applyChange(int16_t change, int8_t cursorPosition) = 0;
		virtual bool validateInput() = 0;
	
	private:
		void (*consumer)(const T& val);
};

//TODO: change bool flag in constructor to Clock* 
class TimeInputState : public InputState<Time>{
	public:
		TimeInputState(void (*consumer)(const Time& val),
						bool initTimeWithClock=false);
		
		// void handleInput(const ButtonEvent& event) override;
	
	protected:
		int16_t getChange(const ButtonEvent& event) const override;
		int8_t maxCursorPosition() const override;
		void applyChange(int16_t change, int8_t cursorPosition) override;
		bool validateInput() override;
		void lcdShowInput() const override;
};



class DateInputState : public InputState<Date>{
	public:
		DateInputState(void (*consumer)(const Date& val));
	protected:
		int16_t getChange(const ButtonEvent& event) const override;
		int8_t maxCursorPosition() const override;
		void applyChange(int16_t change, int8_t cursorPosition) override;
		bool validateInput() override;
		void lcdShowInput() const override;
};


//TODO: instead of 16 bit int use 32 bit, require changes in InputState
class IntInputState : public InputState<int16_t>{
	public:
		IntInputState(void (*consumer)(const int16_t& val),
						int16_t minVal, 
						int16_t maxVal, 
						int16_t initialValue);
	protected:
		const int16_t minVal;
		const int16_t maxVal;
		const int8_t digitsToRepresent;
	
		int16_t getChange(const ButtonEvent& event) const override;
		int8_t maxCursorPosition() const override;
		void applyChange(int16_t change, int8_t cursorPosition) override;
		bool validateInput() override;
		void lcdShowInput() const override;
};


class AlarmState : public State{
	public:
		AlarmState();
		void handleInput(const ButtonEvent& event) override;
};

class StateFactory{
	public:
		static State* createDefaultState();
		static State* createMenuState();
		static State* createInputTimeState(void (*consumer)(const Time& val),
									bool initTimeWithClock);
		static State* createInputDateState(void (*consumer)(const Date& val));
		static State* createInputIntState(void (*consumer)(const int16_t& val),
										int16_t minVal, 
										int16_t maxVal, 
										int16_t initialValue);
		static State* createAlarmState();
};

//DEBUG
void activateAlarm(const Time& t);


template class InputState<Date>;
template class InputState<Time>;
template class InputState<int16_t>;

#endif