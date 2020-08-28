#include "onyxpch.h"
#include "WindowsWindow.h"


#include <Onyx/Graphics/RendererAPI.h>
#include <Onyx/Graphics/RenderCommand.h>
#include <Onyx/Graphics/GraphicsContext.h>

#include <GLFW/glfw3.h>
#include <Platform/OpenGL/OpenGLGraphicsContext.h>
#include <Platform/Vulkan/VulkanGraphicsContext.h>

namespace Onyx {

	static unsigned char s_WindowCount = 0;

	void error_callback(int error, const char* description)
	{
		fprintf(stderr, "Error: %s\n", description);
	}

	WindowsWindow::WindowsWindow()
	{
		//initialize window attribute
		WindowProperties props;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		m_Data.Title = props.Title;
		m_Data.ScrollX = 0;
		m_Data.ScrollY = 0;
		m_Data.Hidden = false;
		Init();
	}

	WindowsWindow::WindowsWindow(const WindowProperties& properties)
	{
		//initialize window attribute
		m_Data.Width = properties.Width;
		m_Data.Height = properties.Height;
		m_Data.Title = properties.Title;
		m_Data.ScrollX = 0;
		m_Data.ScrollY = 0;
		m_Data.Hidden = properties.Hidden;
		Init();
	}

	WindowsWindow::~WindowsWindow()
	{
		delete m_Context;
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void WindowsWindow::Init()
	{
		printf("Title : %s\n", m_Data.Title.c_str());
		
		glfwSetErrorCallback(error_callback);
		if (s_WindowCount == 0 && !glfwInit())	printf("Failed to initialize GLFW!");

		if (RendererAPI::GetAPI() == RendererAPI::API::Vulkan)
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		//EXPERIMENTAL - used for "off-screen" graphics rendering
		if (m_Data.Hidden)
			glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		
		glfwSetWindowUserPointer(m_Window, &m_Data);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;
				RenderCommand::SetViewport(0, 0, width, height);

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
						break;
					}
					case GLFW_REPEAT:
					{
						//KeyPressedEvent event(key, 1);
						//data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			data.ScrollX = xOffset;
			data.ScrollY = yOffset;

		});


		if (RendererAPI::GetAPI() == RendererAPI::API::OpenGL)
			m_Context = new Onyx::OpenGLGraphicsContext(m_Window);

		if(RendererAPI::GetAPI() == RendererAPI::API::Vulkan)
			m_Context = new Onyx::VulkanGraphicsContext(m_Window);

		m_Context->Init();
		
		//if(!m_Data.VSync)
			//glfwSwapInterval(0);
		//else 
		glfwSwapInterval(1);
		
		if(!m_Data.Hidden)
			glfwShowWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		m_Data.ScrollX = 0; m_Data.ScrollY = 0;
		m_Context->SwapBuffers();
		glfwPollEvents();
	}

	void WindowsWindow::SetTitle(const char* title)
	{
		m_Data.Title = title;
		glfwSetWindowTitle(m_Window, title);
	}

	bool WindowsWindow::IsClosed()
	{
		return glfwWindowShouldClose(m_Window) == true;
	}

	bool WindowsWindow::IsHidden()
	{
		return m_Data.Hidden;
	}

}

