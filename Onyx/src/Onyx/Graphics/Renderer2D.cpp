#include "onyxpch.h"
#include "Renderer2D.h"

#include "Shader.h"
#include "VertexArray.h"

#include <memory>

#include <Platform/OpenGL/OpenGLShader.h>
#include "OrthographicCamera.h"

#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>


#include <Onyx/Core/Input.h>


namespace Onyx {

	struct Data{
		VertexArray* VA;
		OpenGLShader* SH;
	};

	static Data* s_Data;

	static OrthographicCamera* m_CameraTest;

	void Renderer2D::init()
	{
		s_Data = new Data();
		VertexArray* quadVA = VertexArray::create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		VertexBuffer* squareVB = VertexBuffer::create(squareVertices, sizeof(squareVertices));
		quadVA->addVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		IndexBuffer* squareIB = IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		quadVA->setIndexBuffer(squareIB);

		//render test
		glEnableVertexAttribArray(0);
		squareVB->bind();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		OpenGLShader* FlatColorShader = (OpenGLShader*)Shader::create("res/shaders/FlatColor.glsl");

		s_Data->VA = quadVA;
		s_Data->SH = FlatColorShader;

		m_CameraTest = new OrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f);

	}

	void Renderer2D::destroy()
	{

	}

	void Renderer2D::beginScene()
	{
		(s_Data->SH)->bind();
		//(s_Data->SH)->uploadUniformMat4("u_ViewProjection", glm::mat4(1.0f));
		//(s_Data->SH)->uploadUniformMat4("u_Transform", glm::mat4(1.0f));

	}

	void Renderer2D::endScene()
	{

	}

	void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		drawQuad(glm::vec3(position, 0.0f), size, color);
	}

	void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		if (Input::isKeyPressed(ONYX_KEY_D)) {
			
			glm::vec3 pos = m_CameraTest->getPosition();
			
			pos.x += 0.001;

			m_CameraTest->setPosition(pos);

		}

		if (Input::isKeyPressed(ONYX_KEY_A)) {

			glm::vec3 pos = m_CameraTest->getPosition();

			pos.x -= 0.001;

			m_CameraTest->setPosition(pos);

		}

		if (Input::isKeyPressed(ONYX_KEY_W)) {

			glm::vec3 pos = m_CameraTest->getPosition();

			pos.y += 0.001;

			m_CameraTest->setPosition(pos);

		}

		if (Input::isKeyPressed(ONYX_KEY_S)) {

			glm::vec3 pos = m_CameraTest->getPosition();

			pos.y -= 0.001;

			m_CameraTest->setPosition(pos);

		}


		(s_Data->SH)->bind();
		(s_Data->SH)->uploadUniformFloat3("vertexColor", color);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->SH->uploadUniformMat4("u_Transform", transform);
		s_Data->SH->uploadUniformMat4("u_ViewProjection", m_CameraTest->getViewProjectionMatrix());


		glDrawElements(GL_TRIANGLES, s_Data->VA->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
	}

}