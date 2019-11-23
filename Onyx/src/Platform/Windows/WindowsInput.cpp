#include "onyxpch.h"

#include "WindowsInput.h"

#include <Onyx/core/Application.h>
#include <GLFW/glfw3.h>

namespace Onyx {

	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::isKeyPressedImplementation(int keycode)
	{
		int keyState = glfwGetKey((GLFWwindow*)Application::get()->getOnyxWindow().getNativeWindow(), keycode);

		return keyState == GLFW_PRESS || keyState == GLFW_REPEAT;
	}

	float WindowsInput::getMouseXImplementation()
	{
		auto window = (GLFWwindow*)Application::get()->getOnyxWindow().getNativeWindow();
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return (float)xpos;
	}

	float WindowsInput::getMouseYImplementation()
	{
		auto window = (GLFWwindow*)Application::get()->getOnyxWindow().getNativeWindow();
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return (float)ypos;
	}



}
