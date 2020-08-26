#include "Sandbox3D.h"

#include "../.../../glfw3/GLFW/glfw3.h"
#include <Onyx/Entity/Entity.h>
#include <Onyx/Model/ModelLoader.h>
#include <Onyx/Graphics/PerspectiveCameraController.h>

using namespace Onyx;
Model* modelTest = nullptr;

Sandbox3D::Sandbox3D()
	: Layer("Sandbox2DSecond")
{

}

void Sandbox3D::OnAttach()
{

	RenderCommand::SetClearColour(glm::vec4(.2f, .2f, .2f, 1.0f));
	RenderCommand::Clear();

	Renderer3D::Init();

	m_Texture1 = Texture2D::Create("res/textures/mario2.png");
	
	modelTest = ModelLoader::LoadFromFile("res/models/Scene.obj");

	m_Scene = new Scene();

	Entity* ent = m_Scene->CreateEntity();
	TransformComponent t = TransformComponent(glm::vec3(0.0f));
	ent->AddComponent<TransformComponent>(t);
	MeshRendererComponent m = MeshRendererComponent(m_FbxMeshTest);
	ent->AddComponent<MeshRendererComponent>(m);

}

void Sandbox3D::OnDetach()
{
	delete m_Texture1;
}

void Sandbox3D::OnUpdate(Timestep timestep)
{
	//SCENE & RENDER
	static PerspectiveCamera cam = PerspectiveCamera(45.0f, 1.777777f, 0.00001f, 100000.0f);
	static float pos = 0;
	pos += 0.1f;
	cam.SetPosition(glm::vec3(0.0f, 10.0f, pos));
	//cam.SetRotation(pos);
	Renderer3D::BeginScene(cam);

	//std::cout << "Num verts " << modelTest->m_Meshes[0]->m_Vertices->size();
	for (size_t i = 0; i < modelTest->m_Meshes.size(); i++)
	{
		Renderer3D::DrawMesh(modelTest->m_Meshes[i], glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(3.0f));
	}
	

	Renderer3D::EndScene();
	Renderer3D::Flush();

	//m_Scene->OnUpdate(timestep);

}
