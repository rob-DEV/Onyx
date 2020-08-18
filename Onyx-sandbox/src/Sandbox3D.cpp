#include "Sandbox3D.h"

#include "../.../../glfw3/GLFW/glfw3.h"

using namespace Onyx;

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
	m_Cube = Mesh::Create(PrimitiveMeshType::Cube);
	m_Cone = Mesh::Create(PrimitiveMeshType::Cone);
	m_FbxMeshTest = Mesh::Create("res/models/CubeTri.fbx");


	
	m_Cube->SetTintColor(glm::vec4(1.0, 0.2, 0.5, 1.0));
	m_Cone->SetTintColor(glm::vec4(0.2, 1.0, 0.5, 1.0));

	m_Scene = new Scene();

	Entity e = m_Scene->CreateEntity();
	e.AddComponent<TransformComponent>();
	e.RemoveComponent<TransformComponent>();
	e.AddComponent<TransformComponent>();

	for (int i = 0; i < 1000; ++i) {

		Entity e = m_Scene->CreateEntity();
		MeshRendererComponent& meshRenderComponent = e.AddComponent<MeshRendererComponent>(m_FbxMeshTest);

	}

}

void Sandbox3D::OnDetach()
{
	delete m_Texture1;
}

void Sandbox3D::OnUpdate(Timestep timestep)
{
	printf("FrameTime : %.4f\n", timestep.GetMilliseconds());

	//SCENE & RENDER
	m_Scene->OnUpdate(timestep);


}
