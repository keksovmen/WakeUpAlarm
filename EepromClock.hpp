#include "Clock.hpp"
#include "ConsumableEvent.hpp"

class EepromClock : public Clock, public ConsumableEvent{
	public:
		EepromClock(int dateAddress);
		virtual void incrementDay() override;
		virtual void setTime(const Time& t) override;
		virtual void setDate(const Date& d) override;
		
	private:
		const int dateAddress;
		
		Date readDate(int address);
		void saveDate(int address);
};