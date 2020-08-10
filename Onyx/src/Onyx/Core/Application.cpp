#include "onyxpch.h"
#include "Application.h"

#include <Platform/Windows/WindowsInput.h>
#include <Platform/Windows/WindowsWindow.h>

#include <Platform/OpenGL/OpenGLRendererAPI.h>
#include <Platform/Vulkan/VulkanRendererAPI.h>
#include <Platform/Vulkan/VulkanSwapchain.h>

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

	void Application::run()
	{
		if (RendererAPI::getAPI() == RendererAPI::API::OpenGL)
			m_RendererAPI = new OpenGLRendererAPI();

		m_RendererAPI->init();
		m_RendererAPI->setViewport(0, 0, m_Window->getWidth(), m_Window->getHeight());
		m_RendererAPI->setClearColor(glm::vec4(.2f, .2f, .2f, 1.0f));

		Renderer2D::init();

		OrthographicCameraController* cameraController = new OrthographicCameraController();
		Texture2D* testMarioTexture = Texture2D::create("res/textures/mario.png");
		Texture2D* testMario2Texture = Texture2D::create("res/textures/mario2.png");

		float scale = 0.01f;
		double previousTime = glfwGetTime();
		int frameCount = 0;

		SoundDevice::init();
		Sound* sound = nullptr;

		while (!m_Window->isClosed()) {

			double currentTime = glfwGetTime();
			frameCount++;

			if (currentTime - previousTime >= 1.0)
			{
				printf("FPS: %d\n", frameCount);
				frameCount = 0; previousTime = currentTime;
			}

			m_Window->onUpdate();
			cameraController->onUpdate();

			m_RendererAPI->clear();
			m_RendererAPI->setViewport(0, 0, m_Window->getWidth(), m_Window->getHeight());

			static const OrthographicCamera& f = cameraController->getCamera();

			Renderer2D::beginScene(f);

			//Renderer2D::drawQuad(glm::vec3(-0.3f, -0.2f, 0.0f), glm::vec2(0.75f, 0.75f), glm::vec4(0.0f, 0.2f, 0.9f, 1.0f));
			Renderer2D::drawQuad(glm::vec3(-0.1f, -0.3f, 0.0f), glm::vec2(0.75f, 0.75f), glm::vec4(0.8f, 0.2f, 0.2f, 1.0f));
			Renderer2D::drawQuad(glm::vec3(0.8f, 0.8f, 0.0f), glm::vec2(0.75f, 0.75f), testMarioTexture);
			Renderer2D::drawQuad(glm::vec3(0.2f, 0.3f, 0.0f), glm::vec2(0.75f, 0.75f), testMario2Texture);


			Renderer2D::endScene();
			Renderer2D::flush();

		

			if (Input::isKeyPressed(ONYX_KEY_F)) {
				if (sound == nullptr) {
					sound = new OpenALSound("res/audio/theringer.wav");
					sound->play();
				}
			}

			if (Input::isKeyPressed(ONYX_KEY_G)) {
				if (sound != nullptr) { 
					delete sound; sound = nullptr; 
				}
			}
			
			if (Input::isKeyPressed(ONYX_KEY_ESCAPE)) {
				break;
			}

			scale += 0.01f;

		}

		//cleanup sound if necessary
		if (sound != nullptr) { delete sound; sound = nullptr; }
	}

	void Application::onEvent(Event& e)
	{
		printf("%s\n",e.getName());
	}

}

