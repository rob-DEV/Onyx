#include "Sandbox2D.h"


//TODO: sort out
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

	Renderer2D::Destroy();

}

void Sandbox2D::OnUpdate(Timestep timestep)
{
	static float rotation = 0.0f;

	static const OrthographicCamera& camera = m_CameraController->GetCamera();
	
	m_CameraController->OnUpdate(timestep);

	rotation += timestep * 45.0f;

	Renderer2D::BeginScene(camera);

	Renderer2D::DrawQuad(glm::vec3(-0.6f, 0.0f, 0.0f), glm::vec2(0.1f, 0.1f), glm::vec4(0.1f, 0.66f, 0.8f, 1.0f));
	Renderer2D::DrawRotatedQuad(glm::vec3(-0.6f, 0.0f, 0.0f), rotation, glm::vec3(0.0f,0.0f,0.0f), glm::vec2(0.1f, 0.1f), glm::vec4(0.1f, 0.66f, 0.8f, 1.0f));

	Renderer2D::DrawQuad(glm::vec3(0.8f, 0.0f, 0.0f), glm::vec2(0.45f, 0.45f), m_Texture1);
	//Renderer2D::DrawRotatedQuad(glm::vec3(0.8f, 0.0f, 0.1f), rotation, glm::vec3(0.0f,0.0f,1.0f), glm::vec2(0.25f, 0.25f), m_Texture2);


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
