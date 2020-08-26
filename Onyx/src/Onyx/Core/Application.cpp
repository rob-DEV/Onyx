#include "onyxpch.h"
#include "Application.h"

#include <Platform/Windows/WindowsInput.h>
#include <Platform/Windows/WindowsWindow.h>

#include <Platform/OpenGL/OpenGLRendererAPI.h>
#include <Platform/Vulkan/VulkanRendererAPI.h>
#include <Platform/OpenAL/OpenALSound.h>


#include <Onyx/Core/TimeStep.h>
#include <Onyx/Graphics/Texture.h>
#include <Onyx/Graphics/RenderCommand.h>
#include <Onyx/Graphics/OrthographicCameraController.h>

#include <GLFW/glfw3.h>

namespace Onyx {
	
	Application* Application::s_Instance = nullptr;

	Application::Application(void)
	{
		//MAIN INITIALISATION

		//Application Instance
		s_Instance = this;

		//Must initialize, to setup Timestep on first frame
		m_LastTime = 0;

		//Window
		printf("Creating Onyx Application and Window!\n");
		m_Window = new WindowsWindow(WindowProperties("Onyx Engine", 1280, 720));

		//Renderer API
		RenderCommand::Init();
		RenderCommand::SetViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
	
		//Sound
		SoundDevice::Init();

		//LayerStack 
		//TODO: abstract to LayerStack
		m_LayerStack = std::vector<Layer*>();

	}

	Application::~Application()
	{
		for (auto layer : m_LayerStack)
		{
			delete layer;
		}

		m_LayerStack.clear();
		delete m_Window;
	}

	

	void Application::Run()
	{
		//INITIALIZE ALL LAYERS
		for (auto layer : m_LayerStack) {
			layer->OnAttach();
		}


		while (!m_Window->IsClosed()) {


			float time = (float)glfwGetTime();
			Timestep timestep(time - m_LastTime);
			m_LastTime = time;

			printf("FrameTime : %.4f\n", timestep.GetMilliseconds());
	

			RenderCommand::Clear();


			for (auto layer : m_LayerStack) {
				layer->OnUpdate(timestep);
			}
			m_Window->OnUpdate();
		
		}

		for (auto layer : m_LayerStack) {
			layer->OnDetach();
		}

	}

}

