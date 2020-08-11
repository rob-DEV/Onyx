#include "onyxpch.h"

#include "WindowsInput.h"

#include <Onyx/core/Application.h>
#include <GLFW/glfw3.h>

namespace Onyx {

	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImplementation(int keycode)
	{
		int keyState = glfwGetKey((GLFWwindow*)Application::Get()->GetOnyxWindow().GetNativeWindow(), keycode);

		return keyState == GLFW_PRESS || keyState == GLFW_REPEAT;
	}

	float WindowsInput::GetMouseXImplementation()
	{
		auto window = (GLFWwindow*)Application::Get()->GetOnyxWindow().GetNativeWindow();
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return (float)xpos;
	}

	float WindowsInput::GetMouseYImplementation()
	{
		auto window = (GLFWwindow*)Application::Get()->GetOnyxWindow().GetNativeWindow();
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return (float)ypos;
	}



}
