#include "onyxpch.h"
#include "EditorRenderer.h"

#include <Onyx/Core/Application.h>

#include <Onyx/Scene/Scene.h>
#include <Onyx/Graphics/Skybox.h>
#include <Onyx/Graphics/VertexArray.h>
#include <Onyx/Graphics/RenderCommand.h>

#include <Onyx/Graphics/ModelLoader.h>

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

namespace Onyx {

	glm::mat4 EditorRenderer::m_MVP = glm::mat4();

	void EditorRenderer::Init()
	{
		//Load EditorIndentifierShader
		ShaderLibrary::Add("3DEditor", Shader::Create("res/shaders/3DEditor.glsl"));

		m_EditorIndentifierShader = ShaderLibrary::Get("3DEditor");

		m_MeshVertexArray = VertexArray::Create();
		m_MeshVertexBuffer = VertexBuffer::Create();

		m_MeshVertexArray->AddVertexBuffer(m_MeshVertexBuffer);

		m_MeshIndexBuffer = IndexBuffer::Create(32000);
		m_MeshVertexArray->SetIndexBuffer(m_MeshIndexBuffer);

		m_MeshVertexBufferBase = new uint32_t[sizeof(EditorIndentifierVertex) * 10000];
		m_MeshVertexBufferWritePtr = m_MeshVertexBufferBase;

		m_MeshIndexBufferBase = new uint32_t[100000];
		m_MeshIndexBufferWritePtr = m_MeshIndexBufferBase;

		//Buffer layout to be abstracted

		//Position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(EditorIndentifierVertex), (void*)offsetof(EditorIndentifierVertex, EditorIndentifierVertex::Position));

		//Color
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(EditorIndentifierVertex), (void*)offsetof(EditorIndentifierVertex, EditorIndentifierVertex::EntityIdentifier));

	}

	void EditorRenderer::Shutdown()
	{

	}

	void EditorRenderer::BeginScene(const Camera& camera)
	{
		m_MVP = camera.GetViewProjectionMatrix();

		m_MeshVertexBufferWritePtr = m_MeshVertexBufferBase;
		m_MeshIndexBufferWritePtr = m_MeshIndexBufferBase;

		m_IndexCount = 0;
		m_VertexCount = 0;

		m_EditorIndentifierShader->Bind();
		m_EditorIndentifierShader->SetMat4("u_ViewProjection", m_MVP);

		m_MeshVertexArray->Bind();
		m_MeshVertexBuffer->Bind();
		m_MeshIndexBuffer->Bind();

	}

	void EditorRenderer::DrawScene(const Scene* scene)
	{
		
		for (auto entity : scene->m_Entities)
		{
			uint32_t entityID = entity->GetID();
			int r = (entityID & 0x000000FF) >> 0;
			int g = (entityID & 0x0000FF00) >> 8;
			int b = (entityID & 0x00FF0000) >> 16;

			float rF = r / 255.0F;
			float gF = g / 255.0F;
			float bF = b / 255.0F;

			glm::vec4 entityIdentifier(rF, gF, bF, 1.0f);

			if (entity->HasComponent<TransformComponent>() && entity->HasComponent<MeshRendererComponent>()) {

				TransformComponent& t = entity->GetComponent<TransformComponent>();

				glm::mat4 transform = glm::translate(glm::mat4(1.0f), t.Position)
					* glm::scale(glm::mat4(1.0f), t.Scale);

				MeshRendererComponent& mr = entity->GetComponent <MeshRendererComponent>();

				for (auto mesh : mr.GetMeshes())
		 		{
		 			for (size_t i = 0; i < mesh.m_Vertices.size(); ++i) {
						((EditorIndentifierVertex*)m_MeshVertexBufferWritePtr)->Position = transform * glm::vec4(mesh.m_Vertices[i].Position, 1.0f);
						((EditorIndentifierVertex*)m_MeshVertexBufferWritePtr)->EntityIdentifier = entityIdentifier;
						m_MeshVertexBufferWritePtr = (char*)m_MeshVertexBufferWritePtr + sizeof(EditorIndentifierVertex);
		 			}
		 
		 			for (size_t i = 0; i < mesh.m_Indices.size(); ++i) {
		 
		 				*m_MeshIndexBufferWritePtr = mesh.m_Indices[i] + m_VertexCount;
		 				m_MeshIndexBufferWritePtr++;
		 
		 			}
		 
		 			m_IndexCount += mesh.m_Indices.size();
		 			m_VertexCount += mesh.m_Vertices.size();
		 		}
			}

		}
	}

	void EditorRenderer::EndScene()
	{
		unsigned long long vertexBufferSize = (unsigned char*)m_MeshVertexBufferWritePtr - (unsigned char*)m_MeshVertexBufferBase;

		if (vertexBufferSize != 0) {
			//set vertex buffer to draw
			m_MeshVertexBuffer->SetData((void*)m_MeshVertexBufferBase, vertexBufferSize);
			m_MeshIndexBuffer->SetData((void*)m_MeshIndexBufferBase, m_IndexCount);
		}
	}

	void EditorRenderer::Flush()
	{
		if (m_IndexCount > 0)
			RenderCommand::DrawIndexed(m_MeshVertexArray, m_IndexCount);
	}

}