#include "onyxpch.h"
#include "EditorInput.h"


namespace Onyx {


	EditorInput::EditorInput()
	{
		m_MousePos = glm::vec2();
		m_MouseButtons = new bool[8];
		for (size_t i = 0; i < 8; ++i)
		{
			m_MouseButtons[i] = false;
		}

		m_Keys = new bool[350];
		for (size_t i = 0; i < 350; ++i)
		{
			m_Keys[i] = false;
		}

	}

	EditorInput::~EditorInput()
	{
		delete[] m_Keys;
		delete[] m_MouseButtons;
	}

	bool EditorInput::IsMouseButtonPressedImplementation(int mouseButton)
	{
		return m_MouseButtons[mouseButton];
	}

	bool EditorInput::IsKeyPressedImplementation(int keycode)
	{
		return m_Keys[keycode];
	}

	glm::vec2 EditorInput::GetMousePositionImplementation()
	{
		
		return m_MousePos;
	}

	glm::vec2 EditorInput::GetMousePositionNormalizedImplementation()
	{
		//normalize to viewport between -1 - 1
		float xposNormalized = (2.0f * (float)m_MousePos.x) / (float)1130 - 1.0f;
		float yposNormalized = (2.0f * (float)m_MousePos.y) / (float)636 - 1.0f;

		return glm::vec2(-xposNormalized, -yposNormalized);
	}

	double EditorInput::GetMouseScrollImplementation()
	{
		return 0;
	}

	void EditorInput::SetMousePositionImplementation(glm::vec2 position)
	{
		this->m_MousePos = position;
	}

	void EditorInput::SetMousePositionImplementation(Input::MousePosition position)
	{
		if (position == Input::MousePosition::CENTER_SCREEN) {
			this->m_MousePos = glm::vec2(1130.0f / 2.0f, 636.0f / 2.0f);
		}
	}

}
