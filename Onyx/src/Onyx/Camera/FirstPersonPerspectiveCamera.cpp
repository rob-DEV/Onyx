#include "onyxpch.h"
#include "FirstPersonPerspectiveCamera.h"
#include <Onyx/Core/Input.h>

#include <glm/gtc/matrix_transform.hpp>


namespace Onyx {

	FirstPersonPerspectiveCamera::FirstPersonPerspectiveCamera(float fov, float aspect, float zNear, float zFar)
		: m_ProjectionMatrix(glm::perspective(glm::radians(fov), aspect, zNear, zFar)), m_ViewMatrix(glm::mat4(1.0f))
	{

		m_ViewMatrix = glm::lookAt(
			m_Position,           // Camera is here
			glm::vec3(0.0f), // and looks here : at the same position, plus "direction"
			glm::vec3(0.0f, -1.0f, 0.0f)                 // Head is up (set to 0,-1,0 to look upside-down)
		);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void FirstPersonPerspectiveCamera::SetProjection(float fov, float aspect, float zNear, float zFar)
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspect, zNear, zFar);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void FirstPersonPerspectiveCamera::RecalculateViewMatrix()
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}


}