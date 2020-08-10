#ifndef _ONYX_PLATFORM_WINDOWS_INPUT_H_
#define _ONYX_PLATFORM_WINDOWS_INPUT_H_

#include <Onyx/Core/Input.h>

namespace Onyx {

	class WindowsInput : public Input {

	protected:
		bool isKeyPressedImplementation(int keycode);
		float getMouseXImplementation();
		float getMouseYImplementation();

	};

}


#endif // !_ONYX_PLATFORM_WINDOWS_INPUT_H_
