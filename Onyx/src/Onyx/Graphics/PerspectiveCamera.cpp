#include "onyxpch.h"
#include "PerspectiveCamera.h"
#include <Onyx/Core/Input.h>

#include <glm/gtc/matrix_transform.hpp>



namespace Onyx {

	PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float zNear, float zFar)
		: m_ProjectionMatrix(glm::perspective(glm::radians(fov), aspect, zNear, zFar)), m_ViewMatrix(glm::mat4(1.0f))
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspectiveCamera::SetProjection(float fov, float aspect, float zNear, float zFar)
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspect, zNear, zFar);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	Ray PerspectiveCamera::ScreenPointToRay() const
	{
		std::pair<float, float> normalizedMouseInput = Input::GetMousePositionNormalized();
		glm::vec2 normalizedMouse = glm::vec2(normalizedMouseInput.first, normalizedMouseInput.second);

		glm::vec2 ray_nds = normalizedMouse;
		glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, -1.0f, 1.0f);
		glm::mat4 invProjMat = glm::inverse(m_ProjectionMatrix);
		glm::vec4 eyeCoords = invProjMat * ray_clip;
		eyeCoords = glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);
		glm::mat4 invViewMat = glm::inverse(m_ViewMatrix);
		glm::vec4 rayWorld = invViewMat * eyeCoords;

		return Ray(m_Position, rayWorld);
	}

	void PerspectiveCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}


}