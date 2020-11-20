#include "onyxpch.h"
#include "EditorCore.h"


//Core Onyx
#include <Onyx/Core/Core.h>
#include <Onyx/Core/Application.h>
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
#include <Onyx/Graphics/Renderer3D.h>
#include <Onyx/Graphics/RenderCommand.h>
#include <Onyx/Camera/OrthographicCameraController.h>
#include <Onyx/Camera/PerspectiveCameraController.h>

//Sound
#include <Onyx/Audio/Sound.h>

//Platform
#include <Platform/Windows/WindowsWindow.h>
#include <Platform/OpenGL/OpenGLRenderer2D.h>
#include <Platform/OpenGL/OpenGLRenderer3D.h>

#include "EditorInput.h"

#include <Onyx/Model/ModelLoader.h>

#include <glad\glad.h>
#include "GLFW/glfw3.h"

#include <Platform/OpenGL/OpenGLFramebuffer.h>

namespace Onyx {

	EditorCore::EditorCore()
	{		
		//Set the context of the engine
		Application::SetContext(ApplicationContext::Editor);

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
		Renderer3D::Init();

		m_EditorTimestep = Timestep(glfwGetTime());

		m_FrameBufferDataPointer = new char[3 * 1280 * 720];

	}

	EditorCore::~EditorCore()
	{
		delete[] m_FrameBufferDataPointer;
	}

	void EditorCore::InitEngineComponents(SceneEditor* sceneEditor)
	{
		m_SceneEditor = sceneEditor;
	}

	void EditorCore::OnUpdate()
	{
		if (Input::IsKeyPressed(ONYX_KEY_L)) {
			if (!swapbuff) {
				swapbuff = true;
				glReadBuffer(GL_COLOR_ATTACHMENT0);
			}
			else {
				swapbuff = false;
				glReadBuffer(GL_COLOR_ATTACHMENT1);
			}
		}

		float time = (float)glfwGetTime();
		Timestep timestep(time - m_EditorTimestep);
		m_SceneEditor->OnUpdate(timestep);
		m_Window->OnUpdate();

		m_EditorTimestep = time;
	}

	RenderedPixelData EditorCore::GetRenderedFrame()
	{
		return RenderCommand::GetRenderedFrameBuffer(m_FrameBufferDataPointer);
	}

	void EditorCore::OnDetach()
	{

	}

	bool* EditorCore::GetInputKeyBuffer()
	{
		return m_EditorToEngineInput->m_Keys;
	}

	bool* EditorCore::GetInputMouseButtonBuffer()
	{
		return m_EditorToEngineInput->m_MouseButtons;
	}

	void EditorCore::SetMousePosition(float x, float y)
	{
		m_EditorToEngineInput->m_MousePos = glm::vec2(x, y);
	}

}