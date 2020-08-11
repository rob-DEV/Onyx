#include "onyxpch.h"
#include "Application.h"

#include <Platform/Windows/WindowsInput.h>
#include <Platform/Windows/WindowsWindow.h>

#include <Platform/OpenGL/OpenGLRendererAPI.h>
#include <Platform/Vulkan/VulkanRendererAPI.h>
#include <Platform/OpenAL/OpenALSound.h>



#include <Onyx/Graphics/Texture.h>
#include <Onyx/Graphics/OrthographicCameraController.h>

#include <GLFW/glfw3.h>


namespace Onyx {
	
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;
		printf("Creating Onyx Application and Window!\n");
		m_Window = new WindowsWindow(WindowProperties("Onyx Engine", 1280, 720));

		if (RendererAPI::GetAPI() == RendererAPI::API::OpenGL)
			m_RendererAPI = new OpenGLRendererAPI();
		if (RendererAPI::GetAPI() == RendererAPI::API::Vulkan)
			m_RendererAPI = new VulkanRendererAPI();

		m_RendererAPI->Init();
		m_RendererAPI->SetViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
		m_RendererAPI->SetClearColor(glm::vec4(.2f, .2f, .2f, 1.0f));

		m_LayerStack = std::vector<Layer*>();
	}

	Application::~Application()
	{
		delete m_RendererAPI;
		delete m_Window;
	}

	

	void Application::Run()
	{
		//INITIALIZE ALL LAYERS
		for (auto layer : m_LayerStack) {
			layer->OnAttach();
		}

		while (!m_Window->IsClosed()) {

			m_Window->OnUpdate();
			
			m_RendererAPI->Clear();
			m_RendererAPI->SetViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());

			for (auto layer : m_LayerStack) {
				layer->OnUpdate();
			}
		


		}

		for (auto layer : m_LayerStack) {
			layer->OnDetach();
		}

	}

	void Application::OnEvent(Event& e)
	{
		printf("%s\n", e.GetName());
	}

}

