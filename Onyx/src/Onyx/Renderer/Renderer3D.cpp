#include "onyxpch.h"
#include "Renderer3D.h"

#include <Onyx/Core/Application.h>

#include <Onyx/Scene/Scene.h>
#include <Onyx/Graphics/Shader.h>
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

	void Renderer3D::Init()
	{
		//Add standard Shaders
		ShaderCache::Add("Skybox", Shader::Create("res/shaders/Skybox.glsl"));
		ShaderCache::Add("3DRuntime", Shader::Create("res/shaders/3DRuntime.glsl"));

		m_StaticBatch.SetBufferLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_VertColor" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float3, "a_Normal" },
			{ ShaderDataType::Float3, "a_Tangent" }
		});
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
				if (!m_StaticBatch.IsInBatch(entity->GetID())) {
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
}