#include "onyxpch.h"
#include "Application.h"

#include <Platform/Windows/WindowsInput.h>
#include <Platform/Windows/WindowsWindow.h>

#include <Platform/OpenGL/OpenGLRendererAPI.h>

#include <Onyx/Graphics/Texture.h>
#include <Onyx/Graphics/OrthographicCameraController.h>

#include <GLFW/glfw3.h>

namespace Onyx {
	
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		printf("Creating Onyx Application and Window!\n");
	

		s_Instance = this;

		m_Window = new WindowsWindow(WindowProperties());

		m_RendererAPI = new OpenGLRendererAPI();
		m_RendererAPI->init();
		m_RendererAPI->setViewport(0, 0, m_Window->getWidth(), m_Window->getHeight());

		m_RendererAPI->setClearColor(glm::vec4(.2f, .2f, .2f, 1.0f));

	}

	Application::~Application()
	{
		delete m_Window;
	}

	void Application::run()
	{
		Renderer2D::init();

		OrthographicCameraController* cameraController = new OrthographicCameraController();
		Texture2D* testMarioTexture = Texture2D::create("res/textures/mario.png");
		float scale = 0.01f;
		double previousTime = glfwGetTime();
		int frameCount = 0;

		while (!m_Window->isClosed()) {

			double currentTime = glfwGetTime();
			frameCount++;

			if (currentTime - previousTime >= 1.0)
			{
				printf("FPS: %d\n" ,frameCount);

				frameCount = 0;
				previousTime = currentTime;
			}

			m_Window->onUpdate();
			cameraController->onUpdate();

			m_RendererAPI->clear();
			m_RendererAPI->setViewport(0, 0, m_Window->getWidth(), m_Window->getHeight());

			//renderer test 
			Renderer2D::beginScene(cameraController->getCamera());
			
			Renderer2D::drawQuad(glm::vec3(-0.6f, 0.0f, 0.0f), glm::vec2(.1, .25), glm::vec4(0.0f, 0.62f, 0.86f, 1.0f));
		
			Renderer2D::drawQuad(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.8f, 1.5f), testMarioTexture);
		
			Renderer2D::drawQuad(glm::vec3(0.0f, -.9, 0.0f), glm::vec2(4.0f, .3f), glm::vec4(0.0f, 0.8f, 0.2f, 1.0f));

			Renderer2D::drawQuad(glm::vec3(0.6f, 0.0f, 0.0f), glm::vec2(.1, .25), glm::vec4(0.0f, 0.62f, 0.86f, 1.0f));

			Renderer2D::endScene();

			if (Input::isKeyPressed(ONYX_KEY_ESCAPE))
				break;

			scale += 0.01;
		}
	}

}

