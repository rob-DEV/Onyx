#include "onyxpch.h"
#include "FirstPersonCameraController.h"

#include <Platform/Windows/WindowsInput.h>

glm::vec2 mouseCenterPosition = glm::vec2(640, 360);

namespace Onyx  {

	FirstPersonCameraController::FirstPersonCameraController() : m_Camera(90.0f, 1280.0f / 720.0f, 0.0001f, 10000000.0f)
	{
		m_ZoomLevel = 90.0f;
		m_Camera.SetPosition(glm::vec3(0, 0, 50.0f));
	}

	void FirstPersonCameraController::OnUpdate(Timestep timestep)
	{
		float testSpeed = 50.0f;
		float dx = 0; //how much we strafe on x
		float dy = 0; //how much we strafe on x
		float dz = 0; //how much we walk on z

		if (Input::IsKeyPressed(ONYX_KEY_W)) {
			dz = 2;
		}
		if (Input::IsKeyPressed(ONYX_KEY_S)) {
			dz = -2;
		}
		if (Input::IsKeyPressed(ONYX_KEY_D)) {
			dx = 2;
		}
		if (Input::IsKeyPressed(ONYX_KEY_A)) {
			dx = -2;
		}
		if (Input::IsKeyPressed(ONYX_KEY_Q)) {
			dy = -2;
		}
		if (Input::IsKeyPressed(ONYX_KEY_E)) {
			dy = 2;
		}

		//process mouse movement


		glm::vec2 mouse_delta = Input::GetMousePosition()
			- mouseCenterPosition;

		const float mouseX_Sensitivity = 0.25f;
		const float mouseY_Sensitivity = 0.00025f;

		m_Camera.m_Yaw -= mouseX_Sensitivity * mouse_delta.x;
		m_Camera.m_Pitch -= mouseY_Sensitivity * mouse_delta.y;


		//mousePosition = glm::vec2(Input::GetMousePosition().first, Input::GetMousePosition().second);

		glm::mat4 mat = m_Camera.GetViewMatrix();

		glm::vec3 forward(mat[0][2], mat[1][2], mat[2][2]);
		glm::vec3 strafe(mat[0][0], mat[1][0], mat[2][0]);
		//glm::vec3 strafe(mat[0][0], mat[1][0], mat[2][0]);

		const float speed = 0.12f;//how fast we move

		m_Camera.m_EyeVector += (-dz * forward + dx * strafe) * speed;

		glm::mat4 matRoll = glm::mat4(1.0f);//identity matrix; 
		glm::mat4 matPitch = glm::mat4(1.0f);//identity matrix
		glm::mat4 matYaw = glm::mat4(1.0f);//identity matrix

		//roll, pitch and yaw are used to store our angles in our class
		matRoll = glm::rotate(matRoll, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		matPitch = glm::rotate(matPitch, m_Camera.m_Pitch, glm::vec3(1.0f, 0.0f, 0.0f));
		matYaw = glm::rotate(matYaw, glm::radians(m_Camera.m_Yaw), glm::vec3(0.0f, 1.0f, 0.0f));

		glm::mat4 rotationMatrix = matRoll * matPitch * matYaw;

		glm::mat4 translate = glm::translate(glm::mat4(1.0f), m_Camera.m_EyeVector);

		m_Camera.m_Transform = rotationMatrix * translate;

		m_Camera.RecalculateViewMatrix();

		Input::SetMousePosition(Input::MousePosition::CENTER_SCREEN);
	}

}