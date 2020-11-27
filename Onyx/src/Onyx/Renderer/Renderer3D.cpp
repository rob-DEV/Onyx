#include "onyxpch.h"
#include "Renderer3D.h"

#include <Onyx/Core/Application.h>

#include <Onyx/Scene/Scene.h>
#include <Onyx/Graphics/Skybox.h>
#include <Onyx/Graphics/VertexArray.h>


#include <Onyx/Graphics/ModelLoader.h>

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <algorithm>
#include <vector>

namespace Onyx {

	glm::mat4 Renderer3D::m_View = glm::mat4();
	glm::mat4 Renderer3D::m_WorldViewProjection = glm::mat4();

	std::array<Texture2D*, 32> Renderer3D::m_TextureSlots = std::array<Texture2D*, 32>();

	void Renderer3D::Init()
	{
		//Add standard Shaders
		ShaderCache::Add("Skybox", Shader::Create("res/shaders/Skybox.glsl"));
		ShaderCache::Add("3DRuntime", Shader::Create("res/shaders/3DRuntime.glsl"));

	}

	void Renderer3D::Shutdown()
	{

	}

	void Renderer3D::BeginScene(const Camera& camera)
	{
		//NOTE: Casted to mat3 to wipe out position data for cube map
		m_View = camera.GetProjectionMatrix() * glm::mat4(glm::mat3(camera.GetViewMatrix()));
		m_WorldViewProjection = camera.GetViewProjectionMatrix();

		m_StaticBatch.Begin();

	}

	void Renderer3D::DrawSkybox(const Scene* scene)
	{
		Shader* skyShader = ShaderCache::Get("Skybox");

		skyShader->Bind();
		skyShader->SetMat4("u_ViewProjection", m_View);

		scene->m_SkyBox->Draw();
	}

	void Renderer3D::DrawScene(const Scene* scene)
	{
		DrawSkybox(scene);

		Shader* meshShader = ShaderCache::Get("3DRuntime");
		meshShader->Bind();
		meshShader->SetMat4("u_ViewProjection", m_WorldViewProjection);
		meshShader->SetFloat3("u_LightPosition", glm::vec3(0.0f, 8.0f, 0.0f));

		for (auto entity : scene->m_Entities)
		{
			if (entity->IsStatic()) {
				//Check if not in static batch

				if (std::find(m_StaticBatch.EntitiesInBatch.begin(), m_StaticBatch.EntitiesInBatch.end(), entity->GetID()) == m_StaticBatch.EntitiesInBatch.end()) {
					if (entity->HasComponent<TransformComponent>() && entity->HasComponent<MeshRendererComponent>()) {
						TransformComponent& t = entity->GetComponent<TransformComponent>();
						MeshRendererComponent& mr = entity->GetComponent<MeshRendererComponent>();

						glm::mat4 transform = glm::translate(glm::mat4(1.0f), t.Position)
							* glm::scale(glm::mat4(1.0f), t.Scale);

						m_StaticBatch.Submit(entity->GetID(), mr.Meshes, transform);
					}
				}
			}
		}

	}

	void Renderer3D::EndScene()
	{
		m_StaticBatch.End();
	}

	void Renderer3D::Flush()
	{
		//m_StaticBatch.Flush();
	}

	void Renderer3D::ResetAndFlush()
	{

	}


	void Renderer3D::RecreateStaticBatchBuffer()
	{

	}

	void Renderer3D::RenderStaticBatch()
	{

	}

	CommonMaterialBuffer::CommonMaterialBuffer(Material* material)
	{
		m_Material = material;


		m_MeshVertexArray = VertexArray::Create();
		m_MeshVertexBuffer = VertexBuffer::Create();

		m_MeshVertexArray->AddVertexBuffer(m_MeshVertexBuffer);

		m_MeshIndexBuffer = IndexBuffer::Create(100000);
		m_MeshVertexArray->SetIndexBuffer(m_MeshIndexBuffer);

		m_MeshVertexBufferBase = new uint32_t[sizeof(Vertex3D) * 50000];
		m_MeshVertexBufferWritePtr = m_MeshVertexBufferBase;

		m_MeshIndexBufferBase = new uint32_t[100000];
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

	}

}