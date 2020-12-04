#include "onyxpch.h"

#include "WindowsInput.h"
#include "WindowsWindow.h"
#include <Onyx/core/Application.h>
#include <GLFW/glfw3.h>

#include <Onyx/Editor/Core/EditorInput.h>

namespace Onyx {

	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsMouseButtonPressedImplementation(int mouseButton)
	{
		int mouseState = glfwGetMouseButton((GLFWwindow*)Application::Get()->GetOnyxWindow().GetNativeWindow(), mouseButton);

		return mouseState == GLFW_PRESS || mouseState == GLFW_REPEAT;
	}

	bool WindowsInput::IsKeyPressedImplementation(int keycode)
	{

		int keyState = glfwGetKey((GLFWwindow*)Application::Get()->GetOnyxWindow().GetNativeWindow(), keycode);

		return keyState == GLFW_PRESS || keyState == GLFW_REPEAT;

	}

	glm::vec2 WindowsInput::GetMousePositionImplementation()
	{
		auto window = (GLFWwindow*)Application::Get()->GetOnyxWindow().GetNativeWindow();
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return glm::vec2((float)xpos, (float)ypos);
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
		float yPos = (float)636 / 2.0f;

		glfwSetCursorPos((GLFWwindow*)window->GetNativeWindow(), (double)xPos, (double)yPos);
	}

	double WindowsInput::GetMouseScrollImplementation()
	{
		Window* window = &Application::Get()->GetOnyxWindow();

		return window->GetScroll();
	}

}
