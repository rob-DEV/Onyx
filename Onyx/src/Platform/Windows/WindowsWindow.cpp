#include "onyxpch.h"
#include "WindowsWindow.h"


#include <Onyx/Graphics/RendererAPI.h>
#include <Onyx/Graphics/GraphicsContext.h>

#include <GLFW/glfw3.h>
#include <Platform/OpenGL/OpenGLGraphicsContext.h>
#include <Platform/Vulkan/VulkanGraphicsContext.h>

#include <Onyx/Event/KeyEvent.h>

namespace Onyx {

	static unsigned char s_WindowCount = 0;


	WindowsWindow::WindowsWindow()
	{
		//initialize window attribute
		WindowProperties props;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		m_Data.Title = props.Title;

		Init();
	}

	WindowsWindow::WindowsWindow(const WindowProperties& properties)
	{
		//initialize window attribute
		m_Data.Width = properties.Width;
		m_Data.Height = properties.Height;
		m_Data.Title = properties.Title;
		Init();
	}

	WindowsWindow::~WindowsWindow()
	{
		delete m_Context;
	}

	void WindowsWindow::Init()
	{
		printf("Title : %s\n", m_Data.Title.c_str());
		
		if (s_WindowCount == 0 && !glfwInit())	printf("Failed to initialize GLFW!");

		if (RendererAPI::GetAPI() == RendererAPI::API::Vulkan)
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		
		glfwSetWindowUserPointer(m_Window, &m_Data);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						//KeyPressedEvent event(key, 0);
						//data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						//KeyReleasedEvent event(key);
						//data.EventCallback(event);
						//break;
					}
					case GLFW_REPEAT:
					{
						//KeyPressedEvent event(key, 1);
						//data.EventCallback(event);
						//break;
					}
				}
			});


		if (RendererAPI::GetAPI() == RendererAPI::API::OpenGL)
			m_Context = new Onyx::OpenGLGraphicsContext(m_Window);

		if(RendererAPI::GetAPI() == RendererAPI::API::Vulkan)
			m_Context = new Onyx::VulkanGraphicsContext(m_Window);

		m_Context->Init();
		
		glfwSwapInterval(1);
		glfwShowWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		m_Context->SwapBuffers();
		glfwPollEvents();
	}

	bool WindowsWindow::IsClosed()
	{
		return glfwWindowShouldClose(m_Window) == true;
	}

}

