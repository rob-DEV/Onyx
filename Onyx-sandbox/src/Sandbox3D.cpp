#include "Sandbox3D.h"

#include <Onyx/Core/Window.h>
#include <Onyx/Event/Event.h>
#include <Onyx/Core/Input.h>

#include <Onyx/Graphics/RenderCommand.h>
#include <Onyx/Graphics/Renderer3D.h>



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

}

void Sandbox3D::OnDetach()
{
	delete m_CameraController;
	delete m_Texture1;
}

void Sandbox3D::OnUpdate(TimeStep timestep)
{

	static const OrthographicCamera& camera = m_CameraController->GetCamera();

	//m_CameraController->OnUpdate();

	Renderer3D::BeginScene(camera);

	Renderer3D::DrawCube(glm::vec3(-100.0f * timestep, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(1.0f,1.0f,1.0f,1.0f));

	Renderer3D::EndScene();
	Renderer3D::Flush();


}
