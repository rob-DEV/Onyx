#include "onyxpch.h"
#include "RuntimeApplication.h"

#include <Onyx/Graphics/RenderCommand.h>
#include <Platform/Windows/WindowsWindow.h>

namespace Onyx {

	RuntimeApplication::RuntimeApplication()
	{
		s_ApplicationContext = ApplicationContext::Runtime;
		//Load Game Assets and run the Game
		//printf("Initializing Onyx Editor\n");
		m_Window = new WindowsWindow(WindowProperties("Onyx Graphics Context", 1130, 636, false));
		//Renderer API
		RenderCommand::Init();
		RenderCommand::SetViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
		RenderCommand::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
		RenderCommand::Clear();

	}

	RuntimeApplication::~RuntimeApplication()
	{

	}

	void RuntimeApplication::Run()
	{
		while (!m_Window->IsClosed()) {
			RenderCommand::Clear();
			m_Window->OnUpdate();
		}
	}

}