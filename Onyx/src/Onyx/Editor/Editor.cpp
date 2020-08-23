#include "onyxpch.h"
#include "Editor.h"


//Core Onyx
#include <Onyx/Core/Core.h>
#include <Onyx/Core/Application.h>
#include <Onyx/Core/Layer.h>
#include <Onyx/Core/Window.h>
#include <Onyx/Core/Input.h >
#include <Onyx/Event/Event.h>

//Scene
#include <Onyx/Scene/Scene.h>
#include <Onyx/Scene/Entity.h>

//Graphics
#include <Onyx/Graphics/Texture.h>
#include <Onyx/Graphics/Mesh.h>

//Renderer
#include <Onyx/Graphics/RendererAPI.h>
#include <Onyx/Graphics/Renderer2D.h>
#include <Onyx/Graphics/Renderer3D.h>
#include <Onyx/Graphics/RenderCommand.h>
#include <Onyx/Graphics/OrthographicCameraController.h>
#include <Onyx/Graphics/PerspectiveCameraController.h>

//Sound
#include <Onyx/Audio/Sound.h>

//PLATFORM
#include <Platform/Windows/WindowsWindow.h>
#include <Platform/OpenGL/OpenGLRenderer2D.h>
#include <Platform/OpenGL/OpenGLRenderer3D.h>

namespace Onyx {

	Editor* Editor::s_EditorInstance = nullptr;

	Editor::Editor()
	{
		s_EditorInstance = this;

		//Window
		printf("Creating Onyx Editor Instance and Graphics Context!\n");
		m_Window = new WindowsWindow(WindowProperties("Onyx Editor", 960, 540, false));

		m_EditorCamera = new PerspectiveCamera(45.0f, 1280.0f / 720.0f, 0.0001f, 10000000.0f);
		m_EditorCamera->SetPosition(glm::vec3(0.0f, 0.0f, 50.0f));
		m_Mesh = Mesh::Create(PrimitiveMeshType::Cube);
		m_Mesh->SetTintColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		//Renderer API
		RenderCommand::Init();
		RenderCommand::SetViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
		RenderCommand::SetClearColour(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
		RenderCommand::Clear();

		//Sound
		SoundDevice::Init();

		//Renderers
		//Renderer2D::Init();
		Renderer3D::Init();


		//LayerStack 
		//TODO: abstract to LayerStack
		//m_LayerStack = std::vector<Layer*>();


	}

	Editor::~Editor()
	{

	}

	void Editor::OnUpdate()
	{
		//printf("Updating!\n");
		RenderCommand::SetClearColour(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
		RenderCommand::Clear();

		Renderer3D::BeginScene(*m_EditorCamera);
		Renderer3D::DrawMesh(m_Mesh, glm::vec3(-25.0f,15.0f, 0.0f), glm::vec3(3.0f));

		for (size_t i = 0; i < 10; i++)
		{
			Renderer3D::DrawRotatedMesh(Mesh::Create(PrimitiveMeshType::Cone), m_Rotation, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(5 * i, 5 * i, 0.0f), glm::vec3(3.0f));
		}

		Renderer3D::DrawRotatedMesh(m_Mesh, m_Rotation, glm::vec3(0.0f,1.0f,0.0f), glm::vec3(0.0f), glm::vec3(3.0f));
		Renderer3D::EndScene();
		Renderer3D::Flush();

		m_Window->OnUpdate();

		m_Rotation += 1.0f;

	}

	RenderedPixelData Editor::GetRenderedFrame()
	{
		return RenderCommand::GetRenderedFrameBuffer();
	}

	void Editor::OnDetach()
	{

	}

}