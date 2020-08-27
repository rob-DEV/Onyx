#include "onyxpch.h"
#include "EditorInput.h"


namespace Onyx {
	
	bool* EditorInput::Keys = new bool[350];

	EditorInput::EditorInput()
	{
			
	}

	EditorInput::~EditorInput()
	{
		delete[] Keys;
	}

	bool EditorInput::IsKeyPressedImplementation(int keycode)
	{
		
			return false;
	}

	glm::vec2 EditorInput::GetMousePositionImplementation()
	{
		return glm::vec2();
	}

	glm::vec2 EditorInput::GetMousePositionNormalizedImplementation()
	{
		return glm::vec2();
	}

	double EditorInput::GetMouseScrollImplementation()
	{
		return 0;
	}

	void EditorInput::SetMousePositionImplementation(glm::vec2 position)
	{

	}

	void EditorInput::SetMousePositionImplementation(Input::MousePosition position)
	{

	}

}
