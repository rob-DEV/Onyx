#include "onyxpch.h"
#include "OrthographicCameraController.h"

#include <Onyx/Core/Input.h>

namespace Onyx {

	OrthographicCameraController::OrthographicCameraController() : m_Camera(-1.6f, 1.6f, -m_ZoomLevel, m_ZoomLevel)
	{

	}

	void OrthographicCameraController::OnUpdate()
	{
		float testSpeed = 0.02f;

		if (Input::IsKeyPressed(ONYX_KEY_D)) {

			glm::vec3 pos = m_Camera.GetPosition();
			pos.x += testSpeed;
			m_Camera.SetPosition(pos);


		}

		if (Input::IsKeyPressed(ONYX_KEY_A)) {

			glm::vec3 pos = m_Camera.GetPosition();
			pos.x -= testSpeed;
			m_Camera.SetPosition(pos);

		}

		if (Input::IsKeyPressed(ONYX_KEY_W)) {

			glm::vec3 pos = m_Camera.GetPosition();
			pos.y += testSpeed;
			m_Camera.SetPosition(pos);

		}

		if (Input::IsKeyPressed(ONYX_KEY_S)) {

			glm::vec3 pos = m_Camera.GetPosition();
			pos.y -= testSpeed;
			m_Camera.SetPosition(pos);

		}

		if (Input::IsKeyPressed(ONYX_KEY_Q)) {

			m_ZoomLevel -= testSpeed;
			m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
			m_Camera.SetProjection(-1.6f * m_ZoomLevel, 1.6f * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		}

		if (Input::IsKeyPressed(ONYX_KEY_E)) {

			
			m_ZoomLevel += testSpeed;
			m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
			m_Camera.SetProjection(-1.6f * m_ZoomLevel, 1.6f * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);


		}
		
	}

}