#include "onyxpch.h"
#include "OpenGLRenderer3D.h"

#include <Onyx/Core/Application.h>

#include <Onyx/Scene/Scene.h>
#include <Onyx/Graphics/RenderCommand.h>
#include <Platform/OpenGL/OpenGLTexture.h>


#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>


namespace Onyx {

	struct Vertex3D {

		glm::vec3 Position;
		glm::vec4 Color;

	};

	struct EditorVertex3D {

		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec4 EntityIdentifier;

	};


	void OpenGLRenderer3D::InitImplementation()
	{
		
		m_MeshVertexArray = (OpenGLVertexArray*)VertexArray::Create();
		m_MeshVertexBuffer = (OpenGLVertexBuffer*)VertexBuffer::Create(MAX_VERTICES);


		m_MeshVertexArray->AddVertexBuffer(m_MeshVertexBuffer);

		m_MeshVertexBuffer->Bind();
		m_MeshVertexArray->Bind();

		FramebufferSpecification fb;
		fb.Width = 1280;
		fb.Height = 720;


		m_Framebuffer = (OpenGLFramebuffer*)Framebuffer::Create(fb);

		m_Framebuffer->Bind();
		
		GLenum buufers[2] = { GL_COLOR_ATTACHMENT0,  GL_COLOR_ATTACHMENT1 };
		glDrawBuffers(2, buufers);
		switch (Application::GetContext())
		{
		case ApplicationContext::Runtime :
			m_MeshShader = (OpenGLShader*)Shader::Create("res/shaders/3DRuntime.glsl");
			//setup layout

			//Position
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, Vertex3D::Position));


			//Color
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, Vertex3D::Color));

			m_MeshVertexBufferBase = new Vertex3D[MAX_VERTICES];
			m_MeshVertexBufferWritePtr = m_MeshVertexBufferBase;

			break;
		case ApplicationContext::Editor:
			m_MeshShader = (OpenGLShader*)Shader::Create("res/shaders/3DEditor.glsl");
			//setup layout

			//Position
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(EditorVertex3D), (void*)offsetof(EditorVertex3D, EditorVertex3D::Position));


			//Color
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(EditorVertex3D), (void*)offsetof(EditorVertex3D, EditorVertex3D::Color));

			//Entity Identifier
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(EditorVertex3D), (void*)offsetof(EditorVertex3D, EditorVertex3D::EntityIdentifier));


			m_MeshVertexBufferBase = new EditorVertex3D[MAX_VERTICES];
			m_MeshVertexBufferWritePtr = m_MeshVertexBufferBase;

			break;
		default:
			printf("ERROR: Invalid Application Context");
			assert(false);
		}

		

		m_MeshIndexBuffer = (OpenGLIndexBuffer*)IndexBuffer::Create(MAX_INDICES);
		m_MeshVertexArray->SetIndexBuffer(m_MeshIndexBuffer);

		m_MeshIndexBufferBase = new uint32_t[MAX_INDICES];
		m_MeshIndexBufferWritePtr = m_MeshIndexBufferBase;

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

		m_MeshShader->Bind();

		((OpenGLShader*)m_MeshShader)->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		((OpenGLShader*)m_MeshShader)->UploadUniformFloat3("u_LightPosition", { 0.0f, -12.8f, 0.0f });

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
		//PURELY testing to see if a concept is viable
		for (auto entity : scene->m_Entities) {

			uint32_t entityID = entity->GetID();
			int r = (entityID & 0x000000FF) >> 0;
			int g = (entityID & 0x0000FF00) >> 8;
			int b = (entityID & 0x00FF0000) >> 16;

			float rF = r / 255.0F;
			float gF = g / 255.0F;
			float bF = b / 255.0F;


			if (entity->HasComponent<TransformComponent>() && entity->HasComponent<MeshRendererComponent>()) {
				
				TransformComponent& t = entity->GetComponent<TransformComponent>();
				MeshRendererComponent& mr = entity->GetComponent<MeshRendererComponent>();

				glm::mat4 transform = glm::translate(glm::mat4(1.0f), t.Position)
					* glm::scale(glm::mat4(1.0f), t.Scale);

				const std::vector<glm::vec3>& vertices = *mr.GetMesh()->m_Vertices;
				const std::vector<uint32_t>& indices = *mr.GetMesh()->m_Indices;

				//submit vertices
				for (int i = 0; i < vertices.size(); ++i) {

					switch (Application::GetContext()) {
					case ApplicationContext::Runtime:
						((Vertex3D*)m_MeshVertexBufferWritePtr)->Position = transform * glm::vec4(vertices[i], 1.0f);
						((Vertex3D*)m_MeshVertexBufferWritePtr)->Color = mr.GetMesh()->m_Color;
						m_MeshVertexBufferWritePtr = static_cast<char*>(m_MeshVertexBufferWritePtr) + sizeof(Vertex3D);
						break;
					case ApplicationContext::Editor:
						((EditorVertex3D*)m_MeshVertexBufferWritePtr)->Position = transform * glm::vec4(vertices[i], 1.0f);
						((EditorVertex3D*)m_MeshVertexBufferWritePtr)->Color = mr.GetMesh()->m_Color;
						((EditorVertex3D*)m_MeshVertexBufferWritePtr)->EntityIdentifier = glm::vec4(0.8, gF, bF, 1.0f);
						m_MeshVertexBufferWritePtr = static_cast<char*>(m_MeshVertexBufferWritePtr) + sizeof(EditorVertex3D);
						break;
					default:
						printf("ERROR: Invalid Application Context");
						assert(false);
					}
				}
				m_VertexCount += vertices.size();

				//submit indices
				//memcpy(m_MeshIndiceBufferWritePtr, &indices[0], indices.size() * sizeof(uint32_t));
				for (int i = 0; i < indices.size(); ++i) {
					*m_MeshIndexBufferWritePtr = indices[i] + m_VertexCount;
					m_MeshIndexBufferWritePtr++;
				}

				m_IndexCount += indices.size();

			}

		}
	}

	void OpenGLRenderer3D::DrawMeshImplementation(const Mesh* mesh, const glm::vec3& position, const glm::vec3& size)
	{

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), size);

		const std::vector<glm::vec3>& vertices = *mesh->m_Vertices;
		const std::vector<uint32_t>& indices = *mesh->m_Indices;

		//submit vertices
		for (int i = 0; i < vertices.size(); ++i) {
			
			switch (Application::GetContext()) {
			case ApplicationContext::Runtime : 
				((Vertex3D*)m_MeshVertexBufferWritePtr)->Position = transform * glm::vec4(vertices[i], 1.0f);
				((Vertex3D*)m_MeshVertexBufferWritePtr)->Color = mesh->m_Color;
				m_MeshVertexBufferWritePtr = static_cast<char*>(m_MeshVertexBufferWritePtr) + sizeof(Vertex3D);
				break;
			case ApplicationContext::Editor :
				((EditorVertex3D*)m_MeshVertexBufferWritePtr)->Position = transform * glm::vec4(vertices[i], 1.0f);
				((EditorVertex3D*)m_MeshVertexBufferWritePtr)->Color = mesh->m_Color;
				((EditorVertex3D*)m_MeshVertexBufferWritePtr)->EntityIdentifier = (glm::vec4(0.0f,0.8f,0.1f,1.0f));
				m_MeshVertexBufferWritePtr = static_cast<char*>(m_MeshVertexBufferWritePtr) + sizeof(EditorVertex3D);
				break;
			default:
				printf("ERROR: Invalid Application Context");
				assert(false);
			}
		}
		m_VertexCount += vertices.size();

		//submit indices
		//memcpy(m_MeshIndiceBufferWritePtr, &indices[0], indices.size() * sizeof(uint32_t));
 		for (int i = 0; i < indices.size(); ++i) {
 			*m_MeshIndexBufferWritePtr = indices[i]  + m_VertexCount;
 			m_MeshIndexBufferWritePtr++;
 		}

		m_IndexCount += indices.size();
	}

	void OpenGLRenderer3D::DrawRotatedMeshImplementation(const Mesh* mesh, float angle, const glm::vec3& ax, const glm::vec3& position, const glm::vec3& size)
	{

	}

}