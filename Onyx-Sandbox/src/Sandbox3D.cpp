#include "Sandbox3D.h"

#include "../.../../glfw3/GLFW/glfw3.h"
#include <Onyx/Entity/Entity.h>
#include <Onyx/Model/ModelLoader.h>
#include <Onyx/Camera/FirstPersonCameraController.h>

#include <Onyx/Scene/Scene.h>

using namespace Onyx;

Model* modelTest = nullptr;

Sandbox3D::Sandbox3D()
	: Layer("Sandbox2DSecond")
{

}

void Sandbox3D::OnAttach()
{

	RenderCommand::SetClearColor(glm::vec4(.2f, .2f, .2f, 1.0f));
	RenderCommand::Clear();

	Renderer3D::Init();

	m_Texture1 = Texture2D::Create("res/textures/mario2.png");
	
	modelTest = ModelLoader::Load("res/models/Scene.obj");

	m_Scene = new Onyx::Scene();

// 	Entity* ent = m_Scene->CreateEntity();
// 	TransformComponent t = TransformComponent(glm::vec3(0.0f));
// 	ent->AddComponent<TransformComponent>(t);
// 	MeshRendererComponent m = MeshRendererComponent(m_FbxMeshTest);
// 	ent->AddComponent<MeshRendererComponent>(m);

}

void Sandbox3D::OnDetach()
{
	delete m_Texture1;
}

void Sandbox3D::OnUpdate(Timestep timestep)
{


	m_Scene->OnUpdate(timestep);
	

	

}
