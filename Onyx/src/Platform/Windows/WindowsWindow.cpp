#include "onyxpch.h"
#include "WindowsWindow.h"


#include <GLFW/glfw3.h>
#include <Platform/OpenGL/OpenGLGraphicsContext.h>

namespace Onyx {

	static unsigned char s_WindowCount = 0;


	WindowsWindow::WindowsWindow() : m_WindowProperties(WindowProperties())
	{
		init();
	}

	WindowsWindow::WindowsWindow(const WindowProperties& properties) : m_WindowProperties(properties)
	{
		init();
	}

	WindowsWindow::~WindowsWindow()
	{
		
	}

	void WindowsWindow::init()
	{
		printf("Title : %s\n", m_WindowProperties.Title.c_str());
		
		
		if (s_WindowCount == 0)
			if (!glfwInit())
				printf("Failed to initialize GLFW!");

		m_Window = glfwCreateWindow(m_WindowProperties.Width, 
									m_WindowProperties.Height, 
									m_WindowProperties.Title.c_str(), nullptr, nullptr);
		
		glfwSetWindowUserPointer(m_Window, &m_WindowProperties);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowProperties& data = *(WindowProperties*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;
			});

		m_Context = new Onyx::OpenGLGraphicsContext(m_Window);

		m_Context->init();
		

		glfwSwapInterval(1);
		glfwShowWindow(m_Window);

	}

	void WindowsWindow::onUpdate()
	{
		m_Context->swapBuffers();
		glfwPollEvents();
	}

	bool WindowsWindow::isClosed()
	{
		return glfwWindowShouldClose(m_Window) == true;
	}

}

