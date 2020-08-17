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

	m_CameraController = new PerspectiveCameraController();

	m_Texture1 = Texture2D::Create("res/textures/mario2.png");
	m_Cube = Mesh::Create(PrimitiveMeshType::Cube);
	m_Cone = Mesh::Create(PrimitiveMeshType::Cone);
	m_FbxMeshTest = Mesh::Create("res/models/CubeTri.fbx");


	
	m_Cube->SetTintColor(glm::vec4(1.0, 0.2, 0.5, 1.0));
	m_Cone->SetTintColor(glm::vec4(0.2, 1.0, 0.5, 1.0));

	m_Scene = new Scene();

	Entity e = m_Scene->CreateEntity();
	Entity e1 = m_Scene->CreateEntity();
	Entity e2 = m_Scene->CreateEntity();
	


}

void Sandbox3D::OnDetach()
{
	delete m_CameraController;
	delete m_Texture1;
}

void Sandbox3D::OnUpdate(Timestep timestep)
{
	printf("FrameTime : %.4f\n", timestep.GetMilliseconds());

	static float rotation = 0.0f;

	//UPDATES
	static const PerspectiveCamera& camera = m_CameraController->GetCamera();
	m_CameraController->OnUpdate(timestep);
	m_Scene->OnUpdate(timestep);

	//LOGIC
	rotation += timestep * 90.0f;
	float scale = 7.0f;


	//RENDER
	Renderer3D::BeginScene(camera);

	Renderer3D::DrawMesh(m_Cube, { 10.0f,0.0f,0.0f }, glm::vec3(scale, scale, scale));
	Renderer3D::DrawRotatedMesh(m_FbxMeshTest, rotation, glm::vec3(1.0f, 1.0f,0.0f), glm::vec3(-10.0f, 0.0, 0.0f), glm::vec3(scale, scale, scale));

	Renderer3D::EndScene();
	Renderer3D::Flush();

}
