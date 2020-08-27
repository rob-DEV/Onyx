#include "onyxpch.h"
#include "FirstPersonCameraController.h"

#include <Platform/Windows/WindowsInput.h>

glm::vec2 mouseCenterPosition = glm::vec2(640, 360);

namespace Onyx  {

	FirstPersonCameraController::FirstPersonCameraController() : m_Camera(90.0f, 1280.0f / 720.0f, 0.0001f, 10000000.0f)
	{
		m_ZoomLevel = 90.0f;
		m_Camera.SetPosition(glm::vec3(0, 0, 50.0f));
	}

	void FirstPersonCameraController::OnUpdate(Timestep timestep)
	{
		float initialFoV = 45.0f;

		float speed = 30.0f; // 3 units / second
		float mouseSpeed = 0.005f;

		glm::vec2 mousePosition = glm::vec2(0.0f);

		m_Camera.horizontalAngle += mouseSpeed  * float(1280 / 2 - mousePosition.x); //timestep
		m_Camera.verticalAngle += mouseSpeed  * float(720 / 2 - mousePosition.y);

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
			m_Camera.m_Position += 0.5;
		}
		if (Input::IsKeyPressed(ONYX_KEY_S)) {
			m_Camera.m_Position -= 0.5;
		}
		if (Input::IsKeyPressed(ONYX_KEY_A)) {
			m_Camera.m_Position -= right * timestep.GetSeconds() * speed;
		}

		if (Input::IsKeyPressed(ONYX_KEY_D)) {
			m_Camera.m_Position += right * timestep.GetSeconds() * speed;
		}

		glm::mat4 viewMatrix = glm::lookAt(
			m_Camera.m_Position,           // Camera is here
			glm::vec3(0, 0, 0), // and looks here : at the same position, plus "direction"
			glm::vec3(0,1,0)                  // Head is up (set to 0,-1,0 to look upside-down)
		);

		m_Camera.m_ViewMatrix = viewMatrix;
		m_Camera.RecalculateViewMatrix();



		//Input::SetMousePosition(Input::MousePosition::CENTER_SCREEN);
	}

}