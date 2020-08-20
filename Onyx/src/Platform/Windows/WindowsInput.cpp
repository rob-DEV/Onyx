#include "onyxpch.h"

#include "WindowsInput.h"
#include "WindowsWindow.h"
#include <Onyx/core/Application.h>
#include <GLFW/glfw3.h>

namespace Onyx {

	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImplementation(int keycode)
	{
		int keyState = glfwGetKey((GLFWwindow*)Application::Get()->GetOnyxWindow().GetNativeWindow(), keycode);

		return keyState == GLFW_PRESS || keyState == GLFW_REPEAT;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImplementation()
	{
		auto window = (GLFWwindow*)Application::Get()->GetOnyxWindow().GetNativeWindow();
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return std::pair<float, float>((float)xpos, (float)ypos);
	}

	std::pair<float, float> WindowsInput::GetMousePositionNormalizedImplementation()
	{
		auto window = (GLFWwindow*)Application::Get()->GetOnyxWindow().GetNativeWindow();
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		//normalize to viewport between -1 - 1
		float xposNormalized = (2.0f * xpos) / (float)Application::Get()->GetOnyxWindow().GetWidth() - 1.0f;
		float yposNormalized = (2.0f * ypos) / (float)Application::Get()->GetOnyxWindow().GetHeight() - 1.0f;

		return std::pair<float, float>(xposNormalized, -yposNormalized);

	}

	double WindowsInput::GetMouseScrollImplementation()
	{
		Window* window = &Application::Get()->GetOnyxWindow();

		return window->GetScroll();
	}

}
