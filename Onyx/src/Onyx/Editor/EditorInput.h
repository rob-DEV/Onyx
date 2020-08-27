#ifndef _ONYX_EDITOR_INPUT_H_
#define _ONYX_EDITOR_INPUT_H_

#include <Onyx/Core/Input.h>

namespace Onyx {

	class ONYX_API EditorInput : public Input
	{
	public:
		EditorInput();
		~EditorInput();


		virtual bool IsKeyPressedImplementation(int keycode);
		virtual glm::vec2 GetMousePositionImplementation();
		virtual glm::vec2 GetMousePositionNormalizedImplementation();
		virtual double GetMouseScrollImplementation();

		virtual void SetMousePositionImplementation(glm::vec2 position);
		virtual void SetMousePositionImplementation(Input::MousePosition position);

		static bool* Keys;
	private:
		friend class Editor;
	};

}
#endif