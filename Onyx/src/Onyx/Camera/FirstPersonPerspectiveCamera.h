#ifndef _ONYX_FP_PERSPECTIVE_CAMERA_H_
#define _ONYX_FP_PERSPECTIVE_CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <Onyx/Core/Core.h>
#include "Camera.h"

namespace Onyx {

	class ONYX_API FirstPersonPerspectiveCamera : public Camera
	{
	public:
		FirstPersonPerspectiveCamera(float fov, float aspect, float zNear, float zFar);


		void SetProjection(float fov, float aspect, float zNear, float zFar);
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }


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
		glm::vec3 m_EyeVector = { 0.0f, 0.0f, 0.0f };

		float m_Roll = 0;
		float m_Pitch = 0;
		float m_Yaw = 0;

		glm::mat4 m_Transform = glm::mat4(1.0f);

		friend class FirstPersonCameraController;
	};

}



#endif // _ONYX_PERSPECTIVE_CAMERA_H_