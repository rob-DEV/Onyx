#include "onyxpch.h"
#include "PerspectiveCamera.h"
#include <Onyx/Core/Input.h>

#include <glm/gtc/matrix_transform.hpp>


namespace Onyx {

	PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float zNear, float zFar)
		: m_ProjectionMatrix(glm::perspective(glm::radians(fov), aspect, zNear, zFar)), m_ViewMatrix(glm::mat4(1.0f))
	{

	}

	void PerspectiveCamera::SetProjectionMatrix(float fov, float aspect, float zNear, float zFar)
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspect, zNear, zFar);
	}

	void PerspectiveCamera::SetPitchAndYaw(float pitch, float yaw)
	{
		m_Pitch = pitch;
		m_Yaw = yaw;

		RecalculateDirection();
	}

	void PerspectiveCamera::RecalculateDirection()
	{
		m_Direction = glm::vec3(
			cos(m_Yaw) * sin(m_Pitch),
			sin(m_Yaw),
			cos(m_Yaw) * cos(m_Pitch)
		);

		// Right vector
		m_Right = glm::vec3(
			sin(m_Pitch - 3.14f / 2.0f),
			0,
			cos(m_Pitch - 3.14f / 2.0f)
		);

		// Up vector : perpendicular to both direction and right
		m_Up = glm::cross(m_Right, m_Direction);

		m_ViewMatrix = glm::lookAt(
			m_Position,           // Camera is here
			m_Position + m_Direction, // and looks here : at the same position, plus "direction"
			m_Up                  // Head is up (set to 0,-1,0 to look upside-down)
		);
	}

}