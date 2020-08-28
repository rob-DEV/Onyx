#include "onyxpch.h"
#include "FirstPersonCameraController.h"

#include <Platform/Windows/WindowsInput.h>

namespace Onyx  {

	FirstPersonCameraController::FirstPersonCameraController() : m_Camera(90.0f, 1280.0f / 720.0f, 0.0001f, 10000000.0f)
	{
		m_ZoomLevel = 90.0f;
		m_Camera.SetPosition(glm::vec3(0, 0, 50.0f));
	}

	void FirstPersonCameraController::OnUpdate(Timestep timestep)
	{
		float initialFoV = 45.0f;

		float speed = 0.3f; // 3 units / second
		float mouseSpeed = 0.03f;

		//m_Camera.horizontalAngle = 180; //timestep
		//m_Camera.verticalAngle  = 0;
		glm::vec2 pos = Input::GetMousePosition();

		printf("MOUSE %.3f, %.3f\n", pos.x, pos.y);
		
		m_Camera.horizontalAngle += mouseSpeed * float(1280 / 2 - (int)pos.x);
		m_Camera.verticalAngle -= mouseSpeed * float(720 / 2 - (int)pos.y);
	

		glm::vec3 direction(
			cos(m_Camera.verticalAngle) * sin(m_Camera.horizontalAngle),
			sin(m_Camera.verticalAngle),
			cos(m_Camera.verticalAngle) * cos(m_Camera.horizontalAngle)
		);

		// Right vector
		glm::vec3 right = glm::vec3(
			sin(m_Camera.horizontalAngle - 3.14f / 2.0f),
			0,
			cos(m_Camera.horizontalAngle - 3.14f / 2.0f)
		);

		// Up vector : perpendicular to both direction and right
		glm::vec3 up = glm::cross(right, direction);


		if (Input::IsKeyPressed(ONYX_KEY_W)) {
			m_Camera.m_Position += direction * speed;
		}
		if (Input::IsKeyPressed(ONYX_KEY_S)) {
			m_Camera.m_Position -= direction *  speed;
		}
		if (Input::IsKeyPressed(ONYX_KEY_A)) {
			m_Camera.m_Position -= right  * speed;
		}

		if (Input::IsKeyPressed(ONYX_KEY_D)) {
			m_Camera.m_Position += right  * speed;
		}

		glm::mat4 viewMatrix = glm::lookAt(
			m_Camera.m_Position,           // Camera is here
			m_Camera.m_Position + direction, // and looks here : at the same position, plus "direction"
			up                  // Head is up (set to 0,-1,0 to look upside-down)
		);

		m_Camera.m_ViewMatrix = viewMatrix;
		m_Camera.RecalculateViewMatrix();

		Input::SetMousePosition(Input::MousePosition::CENTER_SCREEN);
	}

}