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
			glm::vec3(0.0f, 1.0f, 0.0f)                 // Head is up (set to 0,-1,0 to look upside-down)
		);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void FirstPersonPerspectiveCamera::SetProjection(float fov, float aspect, float zNear, float zFar)
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspect, zNear, zFar);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	Ray FirstPersonPerspectiveCamera::ScreenPointToRay() const
	{
		auto normalizedMouseInput = Input::GetMousePositionNormalized();
		glm::vec2 normalizedMouse = glm::vec2(normalizedMouseInput.x, normalizedMouseInput.y);

		glm::vec2 ray_nds = normalizedMouse;
		glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, -1.0f, 1.0f);
		glm::mat4 invProjMat = glm::inverse(m_ProjectionMatrix);
		glm::vec4 eyeCoords = invProjMat * ray_clip;
		eyeCoords = glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);
		glm::mat4 invViewMat = glm::inverse(m_ViewMatrix);
		glm::vec4 rayWorld = invViewMat * eyeCoords;

		return Ray(m_Position, rayWorld);
	}

	void FirstPersonPerspectiveCamera::RecalculateViewMatrix()
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}


}