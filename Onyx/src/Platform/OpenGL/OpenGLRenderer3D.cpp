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


	void OpenGLRenderer3D::InitImplementation()
	{
		
		m_MeshVertexArray = (OpenGLVertexArray*)VertexArray::Create();
		m_MeshVertexBuffer = (OpenGLVertexBuffer*)VertexBuffer::Create(MAX_VERTICES);


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

		m_MeshVertexBufferBase = new Vertex3D[MAX_VERTICES];
		m_MeshVertexBufferWritePtr = m_MeshVertexBufferBase;

		m_MeshIndexBuffer = (OpenGLIndexBuffer*)IndexBuffer::Create(MAX_INDICES);
		m_MeshVertexArray->SetIndexBuffer(m_MeshIndexBuffer);

		m_MeshIndexBufferBase = new uint32_t[MAX_INDICES];
		m_MeshIndexBufferWritePtr = m_MeshIndexBufferBase;



		m_MeshBasicShader = (OpenGLShader*)Shader::Create("res/shaders/basic.glsl");
		m_MeshBasicShader->Bind();

	}

	void OpenGLRenderer3D::DestroyImplementation()
	{
		delete[] m_MeshVertexBufferBase;
		delete m_MeshIndexBuffer;
		delete m_MeshIndexBuffer;
		delete m_MeshVertexArray;
	}

	void OpenGLRenderer3D::BeginSceneImplementation(const OrthographicCamera& camera)
	{
		m_MeshVertexBufferWritePtr = m_MeshVertexBufferBase;
		m_MeshIndexBufferWritePtr = m_MeshIndexBufferBase;
		m_IndexCount = 0;
		m_VertexCount = 0;

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
		unsigned long long vertexBufferSize = (unsigned char*)m_MeshVertexBufferWritePtr - (unsigned char*)m_MeshVertexBufferBase;

		if (vertexBufferSize != 0) {
			//set vertex buffer to draw
			m_MeshVertexBuffer->SetData((void*)m_MeshVertexBufferBase, vertexBufferSize);
			m_MeshIndexBuffer->SetData((void*)m_MeshIndexBufferBase, m_IndexCount);
		}
	}

	void OpenGLRenderer3D::FlushImplementation()
	{
		if (m_IndexCount == 0)
			return;

		RenderCommand::DrawIndexed(m_MeshVertexArray, m_IndexCount);

	}

	void OpenGLRenderer3D::DrawMeshImplementation(const Mesh* mesh, const glm::vec3& position, const glm::vec3& size)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);

		const std::vector<glm::vec3>& vertices = mesh->GetVertices();
		const std::vector<uint32_t>& indices = mesh->GetIndices();


		//submit vertices
		for (int i = 0; i < vertices.size(); i++) {

			m_MeshVertexBufferWritePtr->Position = glm::vec4(vertices[i], 0.0f) + glm::vec4(position, 0.0f);
			m_MeshVertexBufferWritePtr->Color = mesh->Color;
			m_MeshVertexBufferWritePtr++;
		}

		//submit indices
		//memcpy(m_MeshIndiceBufferWritePtr, &indices[0], indices.size() * sizeof(uint32_t));
		for (int i = 0; i < indices.size(); i++) {

			*m_MeshIndexBufferWritePtr = indices[i] + m_VertexCount;
			m_MeshIndexBufferWritePtr++;
		}


		m_VertexCount += vertices.size();
		m_IndexCount += indices.size();
	}

}