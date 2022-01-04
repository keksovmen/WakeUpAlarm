#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H



template<typename T>
class EventHandler{
	public:
		virtual void handleEvent(const T& event) = 0;
};




#endif