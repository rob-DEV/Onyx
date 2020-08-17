#include "onyxpch.h"
#include "PerspectiveCameraController.h"

#include <Onyx/Core/Input.h>


namespace Onyx  {

	PerspectiveCameraController::PerspectiveCameraController() : m_Camera(45.0f, 1280.0f / 720.0f, 0.0001f, 10000000.0f)
	{
		m_ZoomLevel = 45.0f;
		m_Camera.SetPosition(glm::vec3(0, 0, 50.0f));
	}

	void PerspectiveCameraController::OnUpdate(Timestep timestep)
	{
		float testSpeed = 50.0f;

		if (Input::IsKeyPressed(ONYX_KEY_D)) {

			glm::vec3 pos = m_Camera.GetPosition();
			pos.x += testSpeed * (float)timestep;
			m_Camera.SetPosition(pos);

		}

		if (Input::IsKeyPressed(ONYX_KEY_A)) {

			glm::vec3 pos = m_Camera.GetPosition();
			pos.x -= testSpeed * (float)timestep;
			m_Camera.SetPosition(pos);

		}

		if (Input::IsKeyPressed(ONYX_KEY_W)) {

			glm::vec3 pos = m_Camera.GetPosition();
			pos.y += testSpeed * (float)timestep;
			m_Camera.SetPosition(pos);

		}

		if (Input::IsKeyPressed(ONYX_KEY_S)) {

			glm::vec3 pos = m_Camera.GetPosition();
			pos.y -= testSpeed * timestep;
			m_Camera.SetPosition(pos);

		}

		auto mouseScroll = Input::GetMouseScroll();

		if (mouseScroll < 0.0f) {

			m_ZoomLevel += testSpeed * (float)timestep;
			m_ZoomLevel = std::min(m_ZoomLevel, 90.0f);
			m_Camera.SetProjection(m_ZoomLevel, 1280.0f / 720.0f, 0.0001f, 10000000.0f);
			
		}

		if (mouseScroll > 0.0f) {

			m_ZoomLevel -= testSpeed * (float)timestep;
			m_ZoomLevel = std::max(m_ZoomLevel, 20.0f);
			m_Camera.SetProjection(m_ZoomLevel, 1280.0f / 720.0f, 0.0001f, 10000000.0f);

		}

	}

}