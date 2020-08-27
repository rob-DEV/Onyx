#include "onyxpch.h"
#include "FirstPersonPerspectiveCamera.h"
#include <Onyx/Core/Input.h>

#include <glm/gtc/matrix_transform.hpp>


namespace Onyx {

	FirstPersonPerspectiveCamera::FirstPersonPerspectiveCamera(float fov, float aspect, float zNear, float zFar)
		: m_ProjectionMatrix(glm::perspective(glm::radians(fov), aspect, zNear, zFar)), m_ViewMatrix(glm::mat4(1.0f))
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void FirstPersonPerspectiveCamera::SetProjection(float fov, float aspect, float zNear, float zFar)
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspect, zNear, zFar);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void FirstPersonPerspectiveCamera::RecalculateViewMatrix()
	{
		m_ViewMatrix = glm::inverse(m_Transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}


}