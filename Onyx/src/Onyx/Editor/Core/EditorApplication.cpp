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

//Graphics
#include <Onyx/Graphics/Mesh.h>
#include <Onyx/Graphics/Texture.h>

//Renderer
#include <Onyx/Graphics/RendererAPI.h>
#include <Onyx/Graphics/Renderer2D.h>
#include <Onyx/Graphics/RenderCommand.h>

//Sound
#include <Onyx/Audio/Sound.h>

#include <Onyx/Graphics/Renderer2D.h>
#include <Onyx/Editor/Renderer/EditorRenderer3D.h>

#include <Onyx/Graphics/ModelLoader.h>
#include <Platform/Windows/WindowsWindow.h>

#include <GLFW/glfw3.h>

#include "EditorInput.h"
#include "../Components/SceneEditorViewport.h"

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
		m_Window = new WindowsWindow(WindowProperties("Onyx Graphics Context", 1280, 720, true));


		//Redirect Standard Input from Windows GLFW to C# Editor
		m_EditorToEngineInput = new EditorInput();
		Input::RedirectInput(m_EditorToEngineInput);

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

		m_EditorRenderer = new SceneEditorViewport();
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

	void EditorApplication::GetRenderedFrame(int* buffer)
	{
		m_EditorRenderer->RenderFrameToBuffer((uint32_t*)buffer);
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
// 		float scaledX, scaledY;
// 		//1130 / 1.7777777;
// 		scaledX = (x / 1130.0f) * 1280.0f;
// 		scaledY = (y / (1130.0f / 1.777777f)) * 720.0f;

		m_EditorToEngineInput->m_MousePos = glm::vec2(x, y);
	}

}