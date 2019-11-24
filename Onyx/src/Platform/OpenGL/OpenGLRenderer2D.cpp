#include "onyxpch.h"
#include "OpenGLRenderer2D.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include <Platform/OpenGL/OpenGLShader.h>
#include <Onyx/Graphics/VertexArray.h>

struct Data {
	Onyx::VertexArray* VA;
	Onyx::OpenGLShader* SH;
	Onyx::Texture* WhiteTexture;
};

namespace Onyx {
	
	static Data* s_Data;

	void OpenGLRenderer2D::initImplementation()
	{
		s_Data = new Data();
		VertexArray* quadVA = VertexArray::create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		VertexBuffer* squareVB = VertexBuffer::create(squareVertices, sizeof(squareVertices));
		quadVA->addVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		IndexBuffer* squareIB = IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		quadVA->setIndexBuffer(squareIB);
		squareVB->bind();

		glEnableVertexAttribArray(0);

		//index, size of each vertex, type, normalized?, byte size of each vertex packet, offset into packet for data
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 20, (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 20, (void*)12);


		OpenGLShader* shader = (OpenGLShader*)Shader::create("res/shaders/FlatColor.glsl");

		s_Data->VA = quadVA;
		s_Data->SH = shader;

		s_Data->WhiteTexture = Texture2D::create(1, 1);
		uint32_t pureWhiteTexture = 0xffffffff;
		s_Data->WhiteTexture->setData(&pureWhiteTexture, sizeof(uint32_t));
	}

	void OpenGLRenderer2D::destroyImplementation()
	{

	}

	void OpenGLRenderer2D::beginSceneImplementation(const OrthographicCamera& camera)
	{
		(s_Data->SH)->bind();
		(s_Data->SH)->uploadUniformMat4("u_ViewProjection", camera.getViewProjectionMatrix());
	}

	void OpenGLRenderer2D::endSceneImplementation()
	{

	}

	void OpenGLRenderer2D::drawQuadImplementation(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		drawQuad(glm::vec3(position, 0.0f), size, color);
	}

	void OpenGLRenderer2D::drawQuadImplementation(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		(s_Data->SH)->uploadUniformFloat3("u_VertexColor", color);
		s_Data->WhiteTexture->bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, position.z });
		s_Data->SH->uploadUniformMat4("u_Transform", transform);

	}

	void OpenGLRenderer2D::drawQuadImplementation(const glm::vec3& position, const glm::vec2& size, Texture2D* texture)
	{
		s_Data->SH->uploadUniformFloat3("u_VertexColor", glm::vec4(1));
		texture->bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->SH->uploadUniformMat4("u_Transform", transform);

		s_Data->VA->bind();

	}

	void OpenGLRenderer2D::flushImplementation()
	{
		glDrawElements(GL_TRIANGLES, s_Data->VA->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
		glBindTextureUnit(0, 0);
	}

}