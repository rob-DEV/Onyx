#include "Sandbox2DSecond.h"

#include <Onyx/Core/Window.h>
#include <Onyx/Event/Event.h>
#include <Onyx/Core/Input.h>

#include <Onyx/Graphics/RenderCommand.h>
#include <Onyx/Graphics/Renderer2D.h>



#include "../.../../glfw3/GLFW/glfw3.h"

using namespace Onyx;

Sandbox2DSecond::Sandbox2DSecond()
	: Layer("Sandbox2DSecond")
{

}

void Sandbox2DSecond::OnAttach()
{

	//RenderCommand::SetClearColour(glm::vec4(.2f, .2f, .2f, 1.0f));
	//RenderCommand::Clear();

	//Renderer2D::Init();

	m_CameraController = new OrthographicCameraController();
	m_Texture1 = Texture2D::Create("res/textures/mario2.png");

}

void Sandbox2DSecond::OnDetach()
{
	delete m_CameraController;
	delete m_Texture1;
}

void Sandbox2DSecond::OnUpdate()
{

	static const OrthographicCamera& camera = m_CameraController->GetCamera();

	//m_CameraController->OnUpdate();

	Renderer2D::BeginScene(camera);

	Renderer2D::DrawQuad(glm::vec3(-0.8f, 0.0f, 0.0f), glm::vec2(0.45f, 0.45f), m_Texture1);

	Renderer2D::EndScene();
	Renderer2D::Flush();


}
