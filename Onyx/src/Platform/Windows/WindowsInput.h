#ifndef _ONYX_PLATFORM_WINDOWS_INPUT_H_
#define _ONYX_PLATFORM_WINDOWS_INPUT_H_

#include <Onyx/Core/Input.h>

namespace Onyx {

	class WindowsInput : public Input {

	protected:
		virtual bool IsKeyPressedImplementation(int keycode);
		virtual float GetMouseXImplementation();
		virtual float GetMouseYImplementation();
		virtual double GetMouseScrollImplementation();
	};

}


#endif // !_ONYX_PLATFORM_WINDOWS_INPUT_H_
