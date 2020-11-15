#ifndef _ONYX_PLATFORM_WINDOWS_INPUT_H_
#define _ONYX_PLATFORM_WINDOWS_INPUT_H_

#include <Onyx/Core/Input.h>


namespace Onyx {

	class WindowsInput : public Input {

	protected:
		virtual bool IsMouseButtonPressedImplementation(int mouseButton);
		virtual bool IsKeyPressedImplementation(int keycode);
		virtual glm::vec2 GetMousePositionImplementation() override;
		virtual glm::vec2 GetMousePositionNormalizedImplementation() override;

		virtual void SetMousePositionImplementation(glm::vec2 position);
		virtual void SetMousePositionImplementation(Input::MousePosition position);

		virtual double GetMouseScrollImplementation();
	};

}


#endif // !_ONYX_PLATFORM_WINDOWS_INPUT_H_
