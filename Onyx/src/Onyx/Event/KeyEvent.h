#ifndef _ONYX_KEY_EVENT_H_
#define _ONYX_KEY_EVENT_H_

#include "onyxpch.h"
#include <Onyx/Event/Event.h>

namespace Onyx {

	class KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

	protected:
		KeyEvent(int keycode)
			: m_KeyCode(keycode) {}

		int m_KeyCode;
		

	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		virtual const char* GetName() const {
			return "KEY PRESSED EVENT";
		};

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

	private:
		int m_RepeatCount;
	};
}


#endif // !_ONYX_KEY_EVENT_H_
