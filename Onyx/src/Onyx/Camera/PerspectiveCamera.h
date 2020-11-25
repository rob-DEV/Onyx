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

		void SetProjectionMatrix(float fov, float aspect, float zNear, float zFar);

		virtual const glm::mat4& GetProjectionMatrix() const override { return m_ProjectionMatrix; }
		virtual const glm::mat4& GetViewMatrix() const override { return m_ViewMatrix; }
		virtual const glm::mat4& GetViewProjectionMatrix() const override { return m_ProjectionMatrix * m_ViewMatrix; }

		const glm::vec3& GetPositon() const { return m_Position; };
		const glm::vec3& GetDirection() const { return m_Direction; };
		const glm::vec3& GetRight() const { return m_Right; };
		const float GetPitch() const { return m_Pitch; };
		const float GetYaw() const { return m_Yaw; };
		const glm::vec2 GetPitchAndYaw() const { return { m_Pitch, m_Yaw }; };

		void SetPositon(const glm::vec3& positon) {
			m_Position = positon; 
			RecalculateDirection();
		};

		void SetPitch(float pitchAngle) {
			m_Pitch = pitchAngle;
			RecalculateDirection();
		};
		void SetYaw(float yawAngle) {
			m_Yaw = yawAngle; 
			RecalculateDirection();
		};

		//Minimize Recalculation Calls
		void SetPitchAndYaw(float pitch, float yaw);


	private:
		void RecalculateDirection();
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;

		glm::vec3 m_Position = glm::vec3(0.0f);
		glm::vec3 m_Direction = glm::vec3(0.0f);
		//glm::vec3 m_Up = glm::vec3(0.0f);
		glm::vec3 m_Right = glm::vec3(0.0f);

		//+Y is world up
		glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);

		float m_Yaw = 0.0f;
		float m_Pitch = 0.0f;

	};

}



#endif // _ONYX_PERSPECTIVE_CAMERA_H_