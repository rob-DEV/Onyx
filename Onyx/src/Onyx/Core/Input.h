#ifndef _ONYX_INPUT_H_
#define _ONYX_INPUT_H_

#include "Core.h"
#include "Keycodes.h"

namespace Onyx {

	class ONYX_API Input {

	public:
		inline static bool IsKeyPressed(int keycode) {	return s_Instance->IsKeyPressedImplementation(keycode); };
		inline static float GetMouseX() { return s_Instance->GetMouseXImplementation(); };
		inline static float GetMouseY() { return s_Instance->GetMouseYImplementation(); };

		inline static double GetMouseScroll() { return s_Instance->GetMouseScrollImplementation(); };

	protected:
		virtual bool IsKeyPressedImplementation(int keycode) = 0;
		virtual float GetMouseXImplementation() = 0;
		virtual float GetMouseYImplementation() = 0;
		virtual double GetMouseScrollImplementation() = 0;
	
	private:
		static Input* s_Instance;

	};
}

#endif // !_ONYX_INPUT_H_