#ifndef _ONYX_INPUT_H_
#define _ONYX_INPUT_H_

#include "Core.h"
#include "Keycodes.h"

namespace Onyx {

	class ONYX_API Input {

	public:
		inline static bool isKeyPressed(int keycode) {	return s_Instance->isKeyPressedImplementation(keycode); };
		inline static float getMouseX() { return s_Instance->getMouseXImplementation(); };
		inline static float getMouseY() { return s_Instance->getMouseYImplementation(); };

	protected:
		virtual bool isKeyPressedImplementation(int keycode) = 0;
		virtual float getMouseXImplementation() = 0;
		virtual float getMouseYImplementation() = 0;
	
	private:
		static Input* s_Instance;

	};
}

#endif // !_ONYX_APPLICATION_H_