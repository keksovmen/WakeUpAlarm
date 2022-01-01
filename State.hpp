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

class AlarmState : public State{
	public:
		AlarmState();
		void handleInput(const ButtonEvent& event) override;
};

#endif