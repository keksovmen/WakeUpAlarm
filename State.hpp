#ifndef STATE_H
#define STATE_H


#include "EventHandler.hpp"
#include "ButtonsControl.hpp"
#include "Clock.hpp"

#define INPUT_ROW_NUMBER 1


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



class State : public EventHandler<ButtonEvent>{
	protected:
		bool isCancelEvent(const ButtonEvent& event);
		bool isAcceptEvent(const ButtonEvent& event);
};


class DefaultState : public State{
	public:
		DefaultState();
		
		void handleEvent(const ButtonEvent& event) override;
};


class CursorInputState : public State{
	public:
		CursorInputState();
		virtual void handleEvent(const ButtonEvent& event) override;
		
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
		void handleEvent(const ButtonEvent& event) override;
	protected:
		int8_t maxCursorPosition() const override;
		void lcdShowInput() const override;
};


template <typename T>
class InputState : public CursorInputState{
	public:
		InputState(void (*consumer)(const T& val),
					const T& initialValue);
		void handleEvent(const ButtonEvent& event) override;
	
	protected:
		T m_val;
		
		virtual int32_t getChange(const ButtonEvent& event) const = 0;
		virtual void applyChange(int32_t change, int8_t cursorPosition) = 0;
		virtual bool validateInput() = 0;
	
	private:
		void (*consumer)(const T& val);
};


class TimeInputState : public InputState<Time>{
	public:
		TimeInputState(void (*consumer)(const Time& val),
						const Time& initialValue);
	
	protected:
		int32_t getChange(const ButtonEvent& event) const override;
		int8_t maxCursorPosition() const override;
		void applyChange(int32_t change, int8_t cursorPosition) override;
		bool validateInput() override;
		void lcdShowInput() const override;
};


class DateInputState : public InputState<Date>{
	public:
		DateInputState(void (*consumer)(const Date& val),
						const Date& initialValue);
	protected:
		int32_t getChange(const ButtonEvent& event) const override;
		int8_t maxCursorPosition() const override;
		void applyChange(int32_t change, int8_t cursorPosition) override;
		bool validateInput() override;
		void lcdShowInput() const override;
};


//TODO: instead of 16 bit int use 32 bit, require changes in InputState
class IntInputState : public InputState<int32_t>{
	public:
		IntInputState(void (*consumer)(const int32_t& val),
						const int32_t& initialValue,
						int32_t minVal, 
						int32_t maxVal
						);
	protected:
		const int32_t minVal;
		const int32_t maxVal;
		const int8_t digitsToRepresent;
	
		int32_t getChange(const ButtonEvent& event) const override;
		int8_t maxCursorPosition() const override;
		void applyChange(int32_t change, int8_t cursorPosition) override;
		bool validateInput() override;
		void lcdShowInput() const override;
};


class AlarmState : public State{
	public:
		AlarmState(uint8_t alarmId);
		void handleEvent(const ButtonEvent& event) override;
	protected:
		const uint8_t alarmId;
};

class StateFactory{
	public:
		static State* createDefaultState();
		static State* createMenuState();
		static State* createInputTimeState(void (*consumer)(const Time& val),
									const Time& initialValue);
		static State* createInputDateState(void (*consumer)(const Date& val),
									const Date& initialValue);
		static State* createInputIntState(void (*consumer)(const int32_t& val),
									int32_t minVal, 
									int32_t maxVal, 
									int32_t initialValue);
		static State* createAlarmState(uint8_t alarmId);
};


template class InputState<Time>;
template class InputState<Date>;
template class InputState<int32_t>;


#endif