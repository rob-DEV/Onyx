#include "onyxpch.h"
#include "WindowsWindow.h"


#include <Onyx/Graphics/RendererAPI.h>
#include <Onyx/Graphics/GraphicsContext.h>

#include <GLFW/glfw3.h>
#include <Platform/OpenGL/OpenGLGraphicsContext.h>
#include <Platform/Vulkan/VulkanGraphicsContext.h>

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

		//for vulkan specifically
		if (RendererAPI::getAPI() == RendererAPI::API::Vulkan)
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);


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



		if (RendererAPI::getAPI() == RendererAPI::API::OpenGL)
			m_Context = new Onyx::OpenGLGraphicsContext(m_Window);

		if(RendererAPI::getAPI() == RendererAPI::API::Vulkan)
			m_Context = new Onyx::VulkanGraphicsContext(m_Window);

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

