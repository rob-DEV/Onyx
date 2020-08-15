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

	m_CameraController = new OrthographicCameraController();
	m_Texture1 = Texture2D::Create("res/textures/mario2.png");
	m_Mesh = Mesh::Create(PrimitiveMeshType::Cube);

}

void Sandbox3D::OnDetach()
{
	delete m_CameraController;
	delete m_Texture1;
}

void Sandbox3D::OnUpdate(Timestep timestep)
{
	static float rotation = 0.0f;
	static const OrthographicCamera& camera = m_CameraController->GetCamera();

	//m_CameraController->OnUpdate();

	rotation += timestep * 90.0f;

	Renderer3D::BeginScene(camera);

	//Renderer3D::DrawCube(glm::vec3(-100.0f * timestep, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(1.0f,1.0f,1.0f,1.0f));
	m_Mesh->Color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	Renderer3D::DrawMesh(m_Mesh, glm::vec3(0.0, 1.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f));

	for (float x = 0.1f; x < 10; x+= 1.5f)
	{
		for (float y = 0.1f; y < 10; y += 1.5f)
		{
			//float normalized color = x / (1)
			m_Mesh->Color = glm::vec4(0.5f, 1.0f, 0.0f, 1.0f);
			Renderer3D::DrawMesh(m_Mesh, glm::vec3(x, y, 0.0f), glm::vec3(0.015f, 0.015f, 0.015f));
		}
	}



	Renderer3D::EndScene();
	Renderer3D::Flush();

}
