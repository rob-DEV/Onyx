#include "onyxpch.h"
#include "OpenGLRenderer3D.h"
#include <Onyx/Graphics/RenderCommand.h>

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include <array>

namespace Onyx {

	struct Vertex3D {

		glm::vec3 Position;
		glm::vec4 Color;

	};

	const float OpenGLRenderer3D::cube_vertices[] = {
		// front
		-0.5, -0.5,  0.5,
		0.5, -0.5,  0.5,
		0.5,  0.5,  0.5,
		-0.5,  0.5,  0.5,
		// back
		-0.5, -0.5, -0.5,
		0.5, -0.5, -0.5,
		0.5,  0.5, -0.5,
		-0.5,  0.5, -0.5
	};

	const uint32_t OpenGLRenderer3D::cube_elements[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3

	};

	void OpenGLRenderer3D::InitImplementation()
	{
		
		m_MeshVertexArray = (OpenGLVertexArray*)VertexArray::Create();
		m_MeshVertexBuffer = (OpenGLVertexBuffer*)VertexBuffer::Create(MAX_CUBE_VERTICES);


		m_MeshVertexArray->AddVertexBuffer(m_MeshVertexBuffer);

		m_MeshVertexBuffer->Bind();
		m_MeshVertexArray->Bind();

		//setup layout

		//Position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, Vertex3D::Position));


		//Color
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, Vertex3D::Color));

		//TODO: removing const bad idea
		uint32_t* indices = ((uint32_t*)cube_elements);

		m_MeshIndexBuffer = (OpenGLIndexBuffer*)IndexBuffer::Create(indices, 36);
		m_MeshVertexArray->SetIndexBuffer(m_MeshIndexBuffer);

		m_MeshVertexBufferData = new Vertex3D[MAX_CUBE_VERTICES];
		m_MeshVertexBufferWritePtr = m_MeshVertexBufferData;


		m_MeshBasicShader = (OpenGLShader*)Shader::Create("res/shaders/basic.glsl");
		//m_MeshBasicShader->Bind();


		glEnable(GL_DEPTH_TEST);
		//glDepthFunc(GL_LESS);
	}

	void OpenGLRenderer3D::DestroyImplementation()
	{
		delete[] m_MeshVertexBufferData;
		delete m_MeshIndexBuffer;
		delete m_MeshIndexBuffer;
		delete m_MeshVertexArray;
	}

	void OpenGLRenderer3D::BeginSceneImplementation(const OrthographicCamera& camera)
	{
		m_MeshVertexBufferWritePtr = m_MeshVertexBufferData;
		m_IndexCount = 0;

		m_MeshVertexArray->Bind();
		m_MeshVertexBuffer->Bind();
		m_MeshIndexBuffer->Bind();
		m_MeshBasicShader->Bind();

		glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)1280 / (float)720, 0.1f, 100.0f);

		// Camera matrix
		glm::mat4 View = glm::lookAt(
			glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
			glm::vec3(0, 0, 0), // and looks at the origin
			glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
			);

		// Model matrix : an identity matrix (model will be at the origin)
		glm::mat4 Model = glm::mat4(1.0f);

		glm::mat4 mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around

		((OpenGLShader*)m_MeshBasicShader)->UploadUniformMat4("u_ViewProjection",  mvp);

	}

	void OpenGLRenderer3D::EndSceneImplementation()
	{
		unsigned long long vertexBufferSize = (unsigned char*)m_MeshVertexBufferWritePtr - (unsigned char*)m_MeshVertexBufferData;

		if (vertexBufferSize != 0) {
			//set vertex buffer to draw
			m_MeshVertexBuffer->SetData((void*)m_MeshVertexBufferData, vertexBufferSize);
		}
	}

	void OpenGLRenderer3D::FlushImplementation()
	{
		if (m_IndexCount == 0)
			return;

		RenderCommand::DrawIndexed(m_MeshVertexArray, m_IndexCount);

	}

	void OpenGLRenderer3D::DrawCubeImplementation(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color)
	{

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(position.x), glm::vec3(1.0f,1.0f,0.0f))
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, size.z });

		//submit vertices
		for (int i = 0; i < 8; i++) {

			m_MeshVertexBufferWritePtr->Position = glm::vec4(((glm::vec3*)cube_vertices)[i], 1.0f) * transform;
			m_MeshVertexBufferWritePtr->Color = glm::vec4(0.6f, 0.1f, 0.2f, 1.0f);
			m_MeshVertexBufferWritePtr++;
		}
		
		m_IndexCount += 36;

	}


}