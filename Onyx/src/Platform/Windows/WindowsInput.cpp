#include "onyxpch.h"

#include "WindowsInput.h"
#include "WindowsWindow.h"
#include <Onyx/core/Application.h>
#include <GLFW/glfw3.h>

#include <Onyx/Editor/EditorInput.h>

namespace Onyx {

	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImplementation(int keycode)
	{
		//Window* window = &Application::Get()->GetOnyxWindow();

		if (false) {

			int keyState = glfwGetKey((GLFWwindow*)Application::Get()->GetOnyxWindow().GetNativeWindow(), keycode);

			return keyState == GLFW_PRESS || keyState == GLFW_REPEAT;

		}
		else {
			//check if editor is null
			return EditorInput::Keys[keycode];
		}

	}

	glm::vec2 WindowsInput::GetMousePositionImplementation()
	{
		auto window = (GLFWwindow*)Application::Get()->GetOnyxWindow().GetNativeWindow();
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		float xPosF = (float)xpos;
		float yPosF = (float)ypos;

		return glm::vec2((float)xPosF, (float)yPosF);
	}

	glm::vec2 WindowsInput::GetMousePositionNormalizedImplementation()
	{
		auto window = (GLFWwindow*)Application::Get()->GetOnyxWindow().GetNativeWindow();
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		//normalize to viewport between -1 - 1
		float xposNormalized = (2.0f * (float)xpos) / (float)Application::Get()->GetOnyxWindow().GetWidth() - 1.0f;
		float yposNormalized = (2.0f * (float)ypos) / (float)Application::Get()->GetOnyxWindow().GetHeight() - 1.0f;

		return glm::vec2(xposNormalized, -yposNormalized);

	}

	void WindowsInput::SetMousePositionImplementation(glm::vec2 position)
	{
		Window* window = &Application::Get()->GetOnyxWindow();
		glfwSetCursorPos((GLFWwindow*)window->GetNativeWindow(), (double)position.x, (double)position.y);
	}

	void WindowsInput::SetMousePositionImplementation(Input::MousePosition position)
	{
		Window* window = &Application::Get()->GetOnyxWindow();

		float xPos = (float)window->GetWidth() / 2.0f;
		float yPos = (float)window->GetHeight() / 2.0f;

		glfwSetCursorPos((GLFWwindow*)window->GetNativeWindow(), (double)xPos, (double)yPos);
	}

	double WindowsInput::GetMouseScrollImplementation()
	{
		Window* window = &Application::Get()->GetOnyxWindow();

		return window->GetScroll();
	}

}
