#ifndef _ONYX_INPUT_H_
#define _ONYX_INPUT_H_

#include "Core.h"
#include "Keycodes.h"

#include <glm/glm.hpp>

namespace Onyx {

	class ONYX_API Input {

	public:
		enum class MousePosition {
			CENTER_SCREEN = 0
		};


		inline static bool IsKeyPressed(int keycode) {	return s_Instance->IsKeyPressedImplementation(keycode); };
		inline static glm::vec2 GetMousePosition() { return s_Instance->GetMousePositionImplementation(); };
		inline static glm::vec2 GetMousePositionNormalized() { return s_Instance->GetMousePositionNormalizedImplementation(); };
		inline static double GetMouseScroll() { return s_Instance->GetMouseScrollImplementation(); };
		
		inline static void SetMousePosition(glm::vec2 position) { s_Instance->SetMousePositionImplementation(position); };
		inline static void SetMousePosition(Input::MousePosition position) { s_Instance->SetMousePositionImplementation(position); };

	protected:
		virtual bool IsKeyPressedImplementation(int keycode) = 0;
		virtual glm::vec2 GetMousePositionImplementation() = 0;
		virtual glm::vec2 GetMousePositionNormalizedImplementation() = 0;
		virtual double GetMouseScrollImplementation() = 0;

		virtual void SetMousePositionImplementation(glm::vec2 position) = 0;
		virtual void SetMousePositionImplementation(Input::MousePosition position) = 0;

	private:
		static Input* s_Instance;

	};
}

#endif // !_ONYX_INPUT_H_