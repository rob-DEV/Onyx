#include "onyxpch.h"
#include "Renderer3D.h"

#include <Onyx/Core/Application.h>

#include <Onyx/Scene/Scene.h>
#include <Onyx/Graphics/Skybox.h>
#include <Onyx/Graphics/VertexArray.h>
#include <Onyx/Graphics/RenderCommand.h>

#include <Onyx/Graphics/ModelLoader.h>

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

namespace Onyx {

	glm::mat4 Renderer3D::m_View = glm::mat4();
	glm::mat4 Renderer3D::m_WorldViewProjection = glm::mat4();
	Model* Renderer3D::s_TestModel = nullptr;
	Material* Renderer3D::s_TestMaterial = nullptr;

	std::array<Texture2D*, 32> Renderer3D::m_TextureSlots = std::array<Texture2D*, 32>();

	void Renderer3D::Init()
	{
		//Add standard Shaders
		ShaderLibrary::Add("Skybox", Shader::Create("res/shaders/Skybox.glsl"));
		ShaderLibrary::Add("3DRuntime", Shader::Create("res/shaders/3DRuntime.glsl"));

		s_TestModel = ModelLoader::Load("Scene", "res/models/Sphere.fbx");

		m_MeshVertexArray = VertexArray::Create();
		m_MeshVertexBuffer = VertexBuffer::Create();

		m_MeshVertexArray->AddVertexBuffer(m_MeshVertexBuffer);

		m_MeshIndexBuffer = IndexBuffer::Create(32000);
		m_MeshVertexArray->SetIndexBuffer(m_MeshIndexBuffer);

		m_MeshVertexBufferBase = new uint32_t[sizeof(Vertex3D) * 500000];
		m_MeshVertexBufferWritePtr = m_MeshVertexBufferBase;

		m_MeshIndexBufferBase = new uint32_t[10000000];
		m_MeshIndexBufferWritePtr = m_MeshIndexBufferBase;

		//Buffer layout to be abstracted

		//Position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, Vertex3D::Position));

		//Color
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, Vertex3D::Color));

		//Tex-Coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, Vertex3D::TexCoords));

		//Normal
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, Vertex3D::Normal));

		//Tangent
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, Vertex3D::Tangent));

		s_TestMaterial = new Material("res/textures/sphere/diffuse.jpg", "res/textures/sphere/roughness.jpg", "res/textures/sphere/normal.jpg");

	}

	void Renderer3D::Shutdown()
	{

	}

	void Renderer3D::BeginScene(const Camera& camera)
	{
		//NOTE: Casted to mat3 to wipe out position data for cube map
		m_View = camera.GetProjectionMatrix() * glm::mat4(glm::mat3(camera.GetViewMatrix()));
		m_WorldViewProjection = camera.GetViewProjectionMatrix();

		m_MeshVertexBufferWritePtr = m_MeshVertexBufferBase;
		m_MeshIndexBufferWritePtr = m_MeshIndexBufferBase;

		m_IndexCount = 0;
		m_VertexCount = 0;
	}

	void Renderer3D::DrawScene(const Scene* scene)
	{
		Shader* skyShader = ShaderLibrary::Get("Skybox");

		skyShader->Bind();
		skyShader->SetMat4("u_ViewProjection", m_View);

		scene->m_SkyBox->Draw();

		Shader* meshShader = ShaderLibrary::Get("3DRuntime");
		meshShader->Bind();
		meshShader->SetMat4("u_ViewProjection", m_WorldViewProjection);
		meshShader->SetFloat3("u_LightPosition", glm::vec3(0.0f, 12.0f, 0.0f));

		m_MeshVertexArray->Bind();
		m_MeshVertexBuffer->Bind();
		m_MeshIndexBuffer->Bind();

		for (auto entity : scene->m_Entities)
		{
			if (entity->HasComponent<TransformComponent>() && entity->HasComponent<MeshRendererComponent>()) {

				TransformComponent& t = entity->GetComponent<TransformComponent>();

				glm::mat4 transform = glm::translate(glm::mat4(1.0f), t.Position)
					* glm::scale(glm::mat4(1.0f), t.Scale);

				MeshRendererComponent& mr = entity->GetComponent <MeshRendererComponent>();

				for (auto mesh : mr.GetMeshes())
				{
					mesh.m_Material.Bind(meshShader);

					for (size_t i = 0; i < mesh.m_Vertices.size(); ++i) {

						memcpy(m_MeshVertexBufferWritePtr, &mesh.m_Vertices[i], sizeof(Vertex3D));
						((Vertex3D*)m_MeshVertexBufferWritePtr)->Position = transform * glm::vec4(mesh.m_Vertices[i].Position, 1.0f);
						m_MeshVertexBufferWritePtr = (char*)m_MeshVertexBufferWritePtr + sizeof(Vertex3D);
					}

					for (size_t i = 0; i < mesh.m_Indices.size(); ++i) {

						*m_MeshIndexBufferWritePtr = mesh.m_Indices[i] + m_VertexCount;
						m_MeshIndexBufferWritePtr++;

					}

					m_IndexCount += mesh.m_Indices.size();
					m_VertexCount += mesh.m_Vertices.size();

					/*if (m_TextureSlots[0]) {*/
						ResetAndFlush();
					/*}*/
				}
			}

		}	
	}

	void Renderer3D::DrawModel(const Model* scene, const glm::mat4& transform)
	{

	}

	void Renderer3D::EndScene()
	{
		unsigned long long vertexBufferSize = (unsigned char*)m_MeshVertexBufferWritePtr - (unsigned char*)m_MeshVertexBufferBase;

		if (vertexBufferSize != 0) {
			//set vertex buffer to draw
			m_MeshVertexBuffer->SetData((void*)m_MeshVertexBufferBase, vertexBufferSize);
			m_MeshIndexBuffer->SetData((void*)m_MeshIndexBufferBase, m_IndexCount);
		}
	}

	void Renderer3D::Flush()
	{
		if (m_IndexCount > 0)
			RenderCommand::DrawIndexed(m_MeshVertexArray, m_IndexCount);
	}

	void Renderer3D::ResetAndFlush()
	{
		EndScene();
		Flush();

		m_MeshVertexBufferWritePtr = m_MeshVertexBufferBase;
		m_MeshIndexBufferWritePtr = m_MeshIndexBufferBase;

		m_IndexCount = 0;
		m_VertexCount = 0;

	}


}