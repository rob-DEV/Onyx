#include "onyxpch.h"
#include "Editor.h"


//Core Onyx
#include <Onyx/Core/Core.h>
#include <Onyx/Core/Application.h>
#include <Onyx/Core/Layer.h>
#include <Onyx/Core/Window.h>
#include <Onyx/Core/Input.h >

//Scene
#include <Onyx/Scene/Scene.h>

//Graphics
#include <Onyx/Graphics/Texture.h>
#include <Onyx/Graphics/Mesh.h>

//Renderer
#include <Onyx/Graphics/RendererAPI.h>
#include <Onyx/Graphics/Renderer2D.h>
#include <Onyx/Graphics/Renderer3D.h>
#include <Onyx/Graphics/RenderCommand.h>
#include <Onyx/Camera/OrthographicCameraController.h>
#include <Onyx/Camera/PerspectiveCameraController.h>

//Sound
#include <Onyx/Audio/Sound.h>

//PLATFORM
#include <Platform/Windows/WindowsWindow.h>
#include <Platform/OpenGL/OpenGLRenderer2D.h>
#include <Platform/OpenGL/OpenGLRenderer3D.h>

#include "EditorInput.h"

#include <Onyx/Model/ModelLoader.h>

#include "GLFW/glfw3.h"

namespace Onyx {
	

	Editor* Editor::s_EditorInstance = nullptr;

	Editor::Editor()
	{
		
		s_EditorInstance = this;

		//Window
		printf("Creating Onyx Editor Instance and Graphics Context!\n");
		m_Window = new WindowsWindow(WindowProperties("Onyx Editor", 1280, 720, true));


		//Redirect Standard Input from Windows GLFW to C# Editor
		m_EditorToEngineInput = new EditorInput();
		Input::RedirectInput(m_EditorToEngineInput);

		//Renderer API
		RenderCommand::Init();
		RenderCommand::SetViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
		RenderCommand::SetClearColour(glm::vec4(0.8f, 0.5f, 0.2f, 1.0f));
		RenderCommand::Clear();

		//Sound
		SoundDevice::Init();

		//Renderers
		Renderer2D::Init();
		Renderer3D::Init();

		//Initalize editor scene
		m_EditorScene = new Scene();

		m_EditorTimestep = Timestep(glfwGetTime());

		frameBufferDataPointer = new char[3 * 1280 * 720];
	}

	Editor::~Editor()
	{
		delete[] frameBufferDataPointer;
	}

	void Editor::OnUpdate()
	{
		float time = (float)glfwGetTime();
		Timestep timestep(time - m_EditorTimestep);
		m_EditorScene->OnUpdate(timestep);
		m_Window->OnUpdate();
		
		m_EditorTimestep = time;
	}

	RenderedPixelData Editor::GetRenderedFrame()
	{
		return RenderCommand::GetRenderedFrameBuffer(frameBufferDataPointer);
	}

	void Editor::OnDetach()
	{

	}

	void Editor::CreateEntity(glm::vec3 position)
	{
		Entity* a = m_EditorScene->CreateEntity();
		TransformComponent s = TransformComponent(glm::vec3(position));
		a->AddComponent<TransformComponent>(s);

		//For testing
		MeshRendererComponent m = MeshRendererComponent(PrimitiveMesh::Create(PrimitiveMeshType::Cone));
		a->AddComponent<MeshRendererComponent>(m);
	}

	bool* Editor::GetInputKeyBuffer()
	{
		return m_EditorToEngineInput->m_Keys;
	}

	bool* Editor::GetInputMouseButtonBuffer()
	{
		return m_EditorToEngineInput->m_MouseButtons;
	}

	void Editor::SetMousePosition(float x, float y)
	{
		m_EditorToEngineInput->m_MousePos = glm::vec2(x, y);
	}

}