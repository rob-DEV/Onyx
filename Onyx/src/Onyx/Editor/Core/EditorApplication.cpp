#include "onyxpch.h"
#include "EditorApplication.h"


//Core Onyx
#include <Onyx/Core/Core.h>

#include <Onyx/Core/Layer.h>
#include <Onyx/Core/Window.h>
#include <Onyx/Core/Input.h >
#include <Onyx/Console/Console.h>

//Scene
#include <Onyx/Editor/Components/Gizmo.h>
#include <Onyx/Editor/Components/SceneEditor.h>

//Renderer
#include <Onyx/Graphics/RendererAPI.h>
#include <Onyx/Graphics/RenderCommand.h>

//Sound
#include <Onyx/Audio/Sound.h>

#include <Onyx/Editor/Renderer/EditorRenderer3D.h>
#include <Onyx/Graphics/ModelLoader.h>
#include <Platform/Windows/WindowsWindow.h>

#include <GLFW/glfw3.h>

#include "EditorInput.h"

#include "Onyx/Core/Core.h"

#include <Onyx/Math/Random.h>

namespace Onyx {

	EditorApplication::EditorApplication()
	{		
		//Set the context of the engine
		s_Instance = this;
		s_ApplicationContext = ApplicationContext::Editor;

		//Redirect stdout to a console managed by Onyx (Debug Only)
		Console::CreateDebug();

		//Window
		printf("Initializing Onyx Editor\n");
		m_Window = new WindowsWindow(WindowProperties("Onyx Graphics Context", 1130, 636, true));


		//Redirect Standard Input from Windows GLFW to C# Editor
		//m_EditorToEngineInput = new EditorInput();
		//Input::RedirectInput(m_EditorToEngineInput);

		//Renderer API
		RenderCommand::Init();
		RenderCommand::SetViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
		RenderCommand::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
		RenderCommand::Clear();

		//Sound
		SoundDevice::Init();

		//Renderers
		Renderer2D::Init();
		EditorRenderer3D::Init();

		m_SceneEditor = new SceneEditor();
		m_EditorTimestep = Timestep((float)glfwGetTime());

	}

	EditorApplication::~EditorApplication()
	{
		delete m_Window;
	}

	void EditorApplication::InitEngineComponents(SceneEditor* sceneEditor)
	{
		m_SceneEditor = sceneEditor;
	}

	void EditorApplication::OnUpdate()
	{
		float time = (float)glfwGetTime();
		Timestep timestep(time - m_EditorTimestep);
		m_SceneEditor->OnUpdate(timestep);
		m_Window->OnUpdate();
		m_EditorTimestep = time;
	}

	bool* EditorApplication::GetInputKeyBuffer()
	{
		return m_EditorToEngineInput->m_Keys;
	}

	bool* EditorApplication::GetInputMouseButtonBuffer()
	{
		return m_EditorToEngineInput->m_MouseButtons;
	}

	void EditorApplication::SetMousePosition(float x, float y)
	{
		m_EditorToEngineInput->m_MousePos = glm::vec2(x, y);
	}

	void* EditorApplication::GetNativeWindowHandle() const
	{
		return s_Instance->GetOnyxWindow().GetNativeWindowHandle();
	}

}