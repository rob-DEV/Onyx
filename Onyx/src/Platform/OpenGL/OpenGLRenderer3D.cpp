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



		m_MeshBasicShader = (OpenGLShader*)Shader::Create("res/shaders/3DTest.glsl");
		m_MeshBasicShader->Bind();

	}

	void OpenGLRenderer3D::DestroyImplementation()
	{
		delete[] m_MeshVertexBufferBase;
		delete m_MeshIndexBuffer;
		delete m_MeshIndexBuffer;
		delete m_MeshVertexArray;
	}

	void OpenGLRenderer3D::BeginSceneImplementation(const Camera& camera)
	{
		m_MeshVertexBufferWritePtr = m_MeshVertexBufferBase;
		m_MeshIndexBufferWritePtr = m_MeshIndexBufferBase;
		m_IndexCount = 0;
		m_VertexCount = 0;

		m_MeshVertexArray->Bind();
		m_MeshVertexBuffer->Bind();
		m_MeshIndexBuffer->Bind();
		m_MeshBasicShader->Bind();



		((OpenGLShader*)m_MeshBasicShader)->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		((OpenGLShader*)m_MeshBasicShader)->UploadUniformFloat3("u_LightPosition", {0.0f, -4.8f, -15.0f});


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
		RenderCommand::DrawArrays(m_MeshVertexArray, m_VertexCount);
		
		return;
		if(m_IndexCount > 0)
			RenderCommand::DrawIndexed(m_MeshVertexArray, m_IndexCount);
		
	}

	void OpenGLRenderer3D::DrawSceneImplementation(const Scene* scene)
	{
		//render skybox
		//loop all entities and draw
		//lighting
		//PBR

	}

	void OpenGLRenderer3D::DrawMeshImplementation(const Mesh* mesh, const glm::vec3& position, const glm::vec3& size)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), size);

		const std::vector<glm::vec3>& vertices = *mesh->m_Vertices;
		const std::vector<uint32_t>& indices = *mesh->m_Indices;

		//submit vertices
		for (int i = 0; i < vertices.size(); i++) {
			m_MeshVertexBufferWritePtr->Position = transform * glm::vec4(vertices[i], 1.0f);
			m_MeshVertexBufferWritePtr->Color = glm::vec4(1.1f, 0.2f, 0.0f, 1.0f);
			m_MeshVertexBufferWritePtr++;

			//nice orange
			//glm::vec4(1.1f, 0.5f, 0.0f, 1.0f);
		}
		m_VertexCount += vertices.size();

		//submit indices
		//memcpy(m_MeshIndiceBufferWritePtr, &indices[0], indices.size() * sizeof(uint32_t));
 		for (int i = 0; i < indices.size(); i++) {
 			*m_MeshIndexBufferWritePtr = indices[i]  + m_VertexCount;
 			m_MeshIndexBufferWritePtr++;
 		}

		m_IndexCount += indices.size();
	}

	void OpenGLRenderer3D::DrawRotatedMeshImplementation(const Mesh* mesh, float angle, const glm::vec3& ax, const glm::vec3& position, const glm::vec3& size)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			//* glm::rotate(glm::mat4(1.0f), angle, ax)
			* glm::scale(glm::mat4(1.0f), size);

		const std::vector<glm::vec3>& vertices = *mesh->m_Vertices;
		const std::vector<uint32_t>& indices = *mesh->m_Indices;

		//submit vertices
		for (int i = 0; i < vertices.size(); i++) {
			m_MeshVertexBufferWritePtr->Position = transform * glm::vec4(vertices[i], 1.0f);
			m_MeshVertexBufferWritePtr->Color = glm::vec4(1.1f, 0.5f, 0.0f, 1.0f);
			m_MeshVertexBufferWritePtr++;
			//nice orange
			//glm::vec4(1.1f, 0.5f, 0.0f, 1.0f);
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