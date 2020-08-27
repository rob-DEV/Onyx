#ifndef _ONYX_PERSPECTIVE_CAMERA_H_
#define _ONYX_PERSPECTIVE_CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <Onyx/Camera/Camera.h>
#include <Onyx/Physics/Ray.h>

namespace Onyx {

	class ONYX_API PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(float fov, float aspect, float zNear, float zFar);

		void SetProjection(float fov, float aspect, float zNear, float zFar);

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		const glm::quat& GetRotation() const { return m_Rotation; }
		void SetRotation(const glm::quat& rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		Ray ScreenPointToRay() const;

		//CAMERA OVERRIDES
		const glm::mat4& GetProjectionMatrix() const override { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const override { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const override { return m_ViewProjectionMatrix; }

	private:
		void RecalculateViewMatrix();
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::quat m_Rotation;

	};

}



#endif // _ONYX_PERSPECTIVE_CAMERA_H_