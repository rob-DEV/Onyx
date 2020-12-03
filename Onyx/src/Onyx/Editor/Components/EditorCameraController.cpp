#include "onyxpch.h"
#include "EditorCameraController.h"

#include <Onyx/Core/Input.h>
#include <Onyx/Core/Application.h>

namespace Onyx {

	EditorCameraController::EditorCameraController() :
		m_Camera(PerspectiveCamera(45.0f, 16.0f / 9.0f, 0.001, 10000.0))
	{

		m_Camera.SetPositon({ -25.0f, 5.0f, -25.0 });
		m_Camera.SetPitch(3.82f);
		m_Camera.SetYaw(3.141592f);
	}

	EditorCameraController::~EditorCameraController()
	{

	}

	void EditorCameraController::OnUpdate(Timestep ts)
	{
		float moveSpeed = 10.0f * ts.GetSeconds();
		float mouseSpeed = 0.06f * ts.GetSeconds();

		glm::vec2 pos = Input::GetMousePosition();

		if (Input::IsMouseButtonPressed(ONYX_MOUSE_BUTTON_MIDDLE)) {

			Input::SetMousePosition(Input::MousePosition::CENTER_SCREEN);
			Application::Get()->GetOnyxWindow().SetCursor(false);
			glm::vec2 pitchYaw = m_Camera.GetPitchAndYaw();
			m_Camera.SetPitchAndYaw(pitchYaw.x + mouseSpeed * float(1130.0f / 2.0f - pos.x), pitchYaw.y - mouseSpeed * float(636.0f / 2.0f - pos.y));
		}
		else {
			Application::Get()->GetOnyxWindow().SetCursor(true);
		}

		glm::vec3 camPos = m_Camera.GetPositon();

		if (Input::IsKeyPressed(ONYX_KEY_W)) {
			camPos += m_Camera.GetDirection() * moveSpeed;
		}
		if (Input::IsKeyPressed(ONYX_KEY_S)) {
			camPos -= m_Camera.GetDirection() * moveSpeed;
		}
		if (Input::IsKeyPressed(ONYX_KEY_A)) {
			camPos += m_Camera.GetRight() * moveSpeed;
		}

		if (Input::IsKeyPressed(ONYX_KEY_D)) {
			camPos -= m_Camera.GetRight() * moveSpeed;
		}
		if (Input::IsKeyPressed(ONYX_KEY_Q)) {
			camPos.y -= moveSpeed;
		}

		if (Input::IsKeyPressed(ONYX_KEY_E)) {
			camPos.y += moveSpeed;
		}
		m_Camera.SetPositon(camPos);
	}

}
