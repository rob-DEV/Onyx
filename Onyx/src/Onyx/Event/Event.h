#ifndef _ONYX_EVENT_H_
#define _ONYX_EVENT_H_

#include "onyxpch.h"

namespace Onyx {


	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};


	class Event {
	public:
		//virtual EventType getEventType() const = 0;
		virtual const char* getName() const = 0;
		virtual std::string toString() const { return getName(); };
	};

}


#endif // !_ONYX_EVENT_H_
