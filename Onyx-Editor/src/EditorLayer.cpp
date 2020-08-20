#include "EditorLayer.h"

#include "../.../../glfw3/GLFW/glfw3.h"

using namespace Onyx;

EditorSandbox::EditorSandbox()
	: Layer("Sandbox2DSecond")
{

}

void EditorSandbox::OnAttach()
{

	RenderCommand::SetClearColour(glm::vec4(.2f, .2f, .2f, 1.0f));
	RenderCommand::Clear();

	Renderer3D::Init();

	m_Texture1 = Texture2D::Create("res/textures/mario2.png");
	m_Cube = Mesh::Create(PrimitiveMeshType::Cube);
	m_Cone = Mesh::Create(PrimitiveMeshType::Cone);
	m_FbxMeshTest = Mesh::Create("res/models/CubeTri.fbx");


	
	m_Cube->SetTintColor(glm::vec4(1.0, 0.2, 0.5, 1.0));
	m_Cone->SetTintColor(glm::vec4(0.2, 1.0, 0.5, 1.0));

	m_Scene = new Scene();
}

void EditorSandbox::OnDetach()
{
	delete m_Texture1;
}

void EditorSandbox::OnUpdate(Timestep timestep)
{
	//SCENE & RENDER
	m_Scene->OnUpdate(timestep);

}
