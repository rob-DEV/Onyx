#include "onyxpch.h"
#include "Application.h"

#include <Platform/Windows/WindowsInput.h>
#include <Platform/Windows/WindowsWindow.h>

#include <Platform/OpenGL/OpenGLRendererAPI.h>

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

		while (!m_Window->isClosed()) {

			m_Window->onUpdate();
			m_RendererAPI->clear();

			//test resize callback
			m_RendererAPI->setViewport(0, 0, m_Window->getWidth(), m_Window->getHeight());


			//renderer test 
			Renderer2D::beginScene();
			
			Renderer2D::drawQuad(glm::vec3(-0.6f,0,0), glm::vec2(.1,.25), glm::vec4(0.0f, 0.62f, 0.86f, 1.0f));
			
			Renderer2D::drawQuad(glm::vec3(-0.8f, 0, 0), glm::vec2(.1, .25), glm::vec4(0.0f, 0.62f, 0.86f, 1.0f));

			Renderer2D::drawQuad(glm::vec3(0.0f, 0, 0), glm::vec2(0.8f, 1.5f), glm::vec4(0.5f, 0.2f, 0.36f, 1.0f));
			
			Renderer2D::drawQuad(glm::vec3(0.6f, 0, 0), glm::vec2(.1, .25), glm::vec4(0.0f, 0.62f, 0.86f, 1.0f));

			Renderer2D::endScene();

			if (Input::isKeyPressed(ONYX_KEY_G))
				printf("G Key Pressed!\n");

			if (Input::isKeyPressed(ONYX_KEY_ESCAPE))
				break;

		}
	}

}

