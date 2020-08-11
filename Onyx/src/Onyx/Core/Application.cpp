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
	}

	Application::~Application()
	{
		delete m_RendererAPI;
		delete m_Window;
	}

	void Application::Run()
	{
		if (RendererAPI::GetAPI() == RendererAPI::API::OpenGL)
			m_RendererAPI = new OpenGLRendererAPI();
		if (RendererAPI::GetAPI() == RendererAPI::API::Vulkan)
			m_RendererAPI = new VulkanRendererAPI();


		m_RendererAPI->Init();
		m_RendererAPI->SetViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
		m_RendererAPI->SetClearColor(glm::vec4(.2f, .2f, .2f, 1.0f));

		Renderer2D::Init();

		OrthographicCameraController* cameraController = new OrthographicCameraController();
		Texture2D* testMarioTexture = Texture2D::Create("res/textures/mario.png");
		Texture2D* testMario2Texture = Texture2D::Create("res/textures/mario2.png");

		float scale = 0.01f;
		double previousTime = glfwGetTime();
		double previousTime1 = glfwGetTime();
		double deltatime = 0.0f;
		double deltatime1 = 0.0f;
		int frameCount = 0;

		float rotation = 0;

		SoundDevice::Init();
		Sound* sound = nullptr;

		while (!m_Window->IsClosed()) {

			double currentTime = glfwGetTime();
			frameCount++;
			deltatime = currentTime - previousTime1;
			deltatime1 = currentTime - previousTime;
			if (deltatime1 >= 1.0)
			{
				printf("FPS: %d\n", frameCount);
				frameCount = 0; previousTime = currentTime;
			}

			m_Window->OnUpdate();
			cameraController->OnUpdate();

			m_RendererAPI->Clear();
			m_RendererAPI->SetViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());

			static const OrthographicCamera& f = cameraController->GetCamera();

			Renderer2D::BeginScene(f);

			Renderer2D::DrawQuad(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.45f, 0.45f), glm::vec4(0.8f, 0.2f, 0.2f, 1.0f));

			Renderer2D::DrawQuad(glm::vec3(0.8f, 0.0f, 0.0f), glm::vec2(0.45f, 0.45f), testMarioTexture);

			rotation = 12 * deltatime;

			Renderer2D::DrawRotatedQuad(glm::vec3(0.2f, -0.6f, 0.0f), rotation, glm::vec3(0.0f,0.0f, 1.0f), glm::vec2(0.45f, 0.45f), testMarioTexture);

			Renderer2D::EndScene();
			Renderer2D::Flush();

		

			if (Input::IsKeyPressed(ONYX_KEY_F)) {
				if (sound == nullptr) {
					sound = new OpenALSound("res/audio/theringer.wav");
					sound->Play();
				}
			}

			if (Input::IsKeyPressed(ONYX_KEY_G)) {
				if (sound != nullptr) { 
					delete sound; sound = nullptr; 
				}
			}
			
			if (Input::IsKeyPressed(ONYX_KEY_ESCAPE)) {
				break;
			}

			scale += 0.01f;

		}

		//cleanup sound if necessary
		if (sound != nullptr) { delete sound; sound = nullptr; }
	}

	void Application::OnEvent(Event& e)
	{
		printf("%s\n", e.GetName());
	}

}

