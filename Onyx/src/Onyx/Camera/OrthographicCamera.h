#ifndef _ONYX_ORTHOGRAPHIC_CAMERA_H_
#define _ONYX_ORTHOGRAPHIC_CAMERA_H_

#include <Onyx/Camera/Camera.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Onyx {

	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		void SetProjection(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }


		//CAMERA OVERRIDES
		virtual const glm::mat4& GetProjectionMatrix() const override { return m_ProjectionMatrix; }
		virtual const glm::mat4& GetViewMatrix() const  override { return m_ViewMatrix; }
		virtual const glm::mat4 GetViewProjectionMatrix() const override { return m_ViewProjectionMatrix; }
		
		virtual const glm::mat4& GetTransform() const { 
			return glm::translate(glm::mat4(1.0f), m_Position)
				* glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
		}

	private:
		void RecalculateViewMatrix();
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
	};

}



#endif // _ONYX_ORTHOGRAPHIC_CAMERA_H_