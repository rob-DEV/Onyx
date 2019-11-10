#include "onyxpch.h"
#include "Application.h"

#include <Platform/Windows/WindowsInput.h>
#include <Platform/Windows/WindowsWindow.h>

#include <Platform/OpenGL/OpenGLRendererAPI.h>

#include <Onyx/Graphics/Texture.h>
#include <Onyx/Graphics/OrthographicCameraController.h>

#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_internal.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

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

	void MySaveFunction() {

	}
	void Application::run()
	{
		Renderer2D::init();

		OrthographicCameraController* cameraController = new OrthographicCameraController();
		Texture2D* testMarioTexture = Texture2D::create("res/textures/mario.png");
		float scale = 0.01f;
		double previousTime = glfwGetTime();
		int frameCount = 0;

		//imgui test
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application& app = *Application::get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.getOnyxWindow().getNativeWindow());

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");

		// Setup Dear ImGui style
		while (!m_Window->isClosed()) {
			

			double currentTime = glfwGetTime();
			frameCount++;


			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			static bool show = true;
			ImGui::ShowDemoWindow(&show);
		

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				GLFWwindow* backup_current_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backup_current_context);
			}

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

