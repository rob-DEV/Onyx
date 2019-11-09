#include "onyxpch.h"
#include "OrthographicCameraController.h"

#include <Onyx/Core/Input.h>

namespace Onyx {

	OrthographicCameraController::OrthographicCameraController() : m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{

	}

	void OrthographicCameraController::onUpdate()
	{
		float testSpeed = 0.02;

		if (Input::isKeyPressed(ONYX_KEY_D)) {

			glm::vec3 pos = m_Camera.getPosition();
			pos.x += testSpeed;
			m_Camera.setPosition(pos);

		}

		if (Input::isKeyPressed(ONYX_KEY_A)) {

			glm::vec3 pos = m_Camera.getPosition();
			pos.x -= testSpeed;
			m_Camera.setPosition(pos);

		}

		if (Input::isKeyPressed(ONYX_KEY_W)) {

			glm::vec3 pos = m_Camera.getPosition();
			pos.y += testSpeed;
			m_Camera.setPosition(pos);

		}

		if (Input::isKeyPressed(ONYX_KEY_S)) {

			glm::vec3 pos = m_Camera.getPosition();
			pos.y -= testSpeed;
			m_Camera.setPosition(pos);

		}

	}

}