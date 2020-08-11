#include "Sandbox2D.h"

#include <Onyx/Core/Window.h>
#include <Onyx/Event/Event.h>
#include <Onyx/Core/Input.h>

#include <Onyx/Graphics/RenderCommand.h>
#include <Onyx/Graphics/Renderer2D.h>



#include "../.../../glfw3/GLFW/glfw3.h"

using namespace Onyx;

Sandbox2D::Sandbox2D()
	: Layer("Sandbox")
{

}

void Sandbox2D::OnAttach()
{
	RenderCommand::SetClearColour(glm::vec4(.2f, .2f, .2f, 1.0f));
	RenderCommand::Clear();

	Renderer2D::Init();

	m_CameraController = new OrthographicCameraController();
	m_Texture1 = Texture2D::Create("res/textures/mario.png");
	m_Texture2 = Texture2D::Create("res/textures/mario2.png");

	m_Sound = Sound::Create("res/audio/theringer.wav");

}

void Sandbox2D::OnDetach()
{
	delete m_CameraController;
	delete m_Texture1;
	delete m_Texture2;

	delete m_Sound;
}

void Sandbox2D::OnUpdate()
{

	static const OrthographicCamera& camera = m_CameraController->GetCamera();

	m_CameraController->OnUpdate();

	Renderer2D::BeginScene(camera);

	Renderer2D::DrawQuad(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.1f, 0.1f), glm::vec4(0.8f, 0.2f, 0.2f, 1.0f));

	Renderer2D::DrawQuad(glm::vec3(0.8f, 0.0f, 0.0f), glm::vec2(0.45f, 0.45f), m_Texture1);

	Renderer2D::EndScene();
	Renderer2D::Flush();


	if (Input::IsKeyPressed(ONYX_KEY_SPACE)) {
		
		if (m_Sound->IsPlaying()) {
			m_Sound->Pause();
		}
		else {
			m_Sound->Play();
		}


	}


}
