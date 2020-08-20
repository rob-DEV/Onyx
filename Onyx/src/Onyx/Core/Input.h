#ifndef _ONYX_INPUT_H_
#define _ONYX_INPUT_H_

#include "Core.h"
#include "Keycodes.h"

namespace Onyx {

	class ONYX_API Input {

	public:
		inline static bool IsKeyPressed(int keycode) {	return s_Instance->IsKeyPressedImplementation(keycode); };
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImplementation(); };
		inline static std::pair<float, float> GetMousePositionNormalized() { return s_Instance->GetMousePositionNormalizedImplementation(); };

		inline static double GetMouseScroll() { return s_Instance->GetMouseScrollImplementation(); };

	protected:
		virtual bool IsKeyPressedImplementation(int keycode) = 0;
		virtual std::pair<float, float> GetMousePositionImplementation() = 0;
		virtual std::pair<float, float>  GetMousePositionNormalizedImplementation() = 0;
		virtual double GetMouseScrollImplementation() = 0;
	
	private:
		static Input* s_Instance;

	};
}

#endif // !_ONYX_INPUT_H_