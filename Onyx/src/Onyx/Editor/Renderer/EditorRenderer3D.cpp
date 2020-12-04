#include "onyxpch.h"
#include "EditorRenderer3D.h"

#include <Onyx/Core/Application.h>

#include <Onyx/Scene/Scene.h>
#include <Onyx/Graphics/Shader.h>
#include <Onyx/Graphics/Skybox.h>
#include <Onyx/Graphics/VertexArray.h>

#include <Onyx/Graphics/ModelLoader.h>
#include <Onyx/Graphics/Framebuffer.h>

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <Onyx/Graphics/RenderCommand.h>

#include <algorithm>
#include <vector>

namespace Onyx {

	glm::mat4 EditorRenderer3D::m_View = glm::mat4();
	glm::mat4 EditorRenderer3D::m_WorldViewProjection = glm::mat4();
	Framebuffer* EditorRenderer3D::m_Framebuffer = nullptr;

	void EditorRenderer3D::Init()
	{
		ShaderCache::Add("Skybox", Shader::Create("res/shaders/Skybox.glsl"));
		ShaderCache::Add("3DEditor", Shader::Create("res/shaders/3DEditor.glsl"));
		ShaderCache::Add("RenderTexture", Shader::Create("res/shaders/RenderTexture.glsl"));

		m_StaticBatch.SetBufferLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_VertColor" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float3, "a_Normal" },
			{ ShaderDataType::Float3, "a_Tangent" },
			{ ShaderDataType::Float4, "a_EntityIdentifier" }
			});
		
		FramebufferSpecification fbSpec(1130, 636, 2, true);

		fbSpec.MultiSample = true;
		fbSpec.Samples = 4;

		m_Framebuffer = Framebuffer::Create(fbSpec);

	}

	void EditorRenderer3D::Shutdown()
	{

	}

	void EditorRenderer3D::BeginScene(const Camera& camera)
	{
		//Bind Framebuffer
		m_Framebuffer->Bind();
		uint32_t w = m_Framebuffer->GetSpecification().Width;
		uint32_t h = m_Framebuffer->GetSpecification().Height;
		RenderCommand::Clear();

		//NOTE: Casted to mat3 to wipe out position data for cube map
		m_View = camera.GetProjectionMatrix() * glm::mat4(glm::mat3(camera.GetViewMatrix()));
		m_WorldViewProjection = camera.GetViewProjectionMatrix();

		m_StaticBatch.Begin();


	}

	void EditorRenderer3D::DrawScene(const Scene* scene)
	{
 		Shader* skyboxShader = ShaderCache::Get("Skybox");
 		skyboxShader->Bind();
 		skyboxShader->SetMat4("u_ViewProjection", m_View);
 		scene->m_SkyBox->Draw();

		Shader* meshShader = ShaderCache::Get("3DEditor");
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

	void EditorRenderer3D::EndScene()
	{
		
		m_StaticBatch.End();

		m_Framebuffer->Unbind();

		//All rendered to framebuffer
		//get framebuffer texture 
		//render to viewport
		GLuint quad_VertexArrayID;
		glGenVertexArrays(1, &quad_VertexArrayID);
		glBindVertexArray(quad_VertexArrayID);

		static const GLfloat g_quad_vertex_buffer_data[] = {
			-1.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			-1.0f,  1.0f, 0.0f,
			-1.0f,  1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			1.0f,  1.0f, 0.0f,
		};

		GLuint quad_vertexbuffer;
		glGenBuffers(1, &quad_vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);

		Shader* renderTextureShader = ShaderCache::Get("RenderTexture");
		renderTextureShader->Bind();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_Framebuffer->GetColorAttachmentRendererID(0));
		renderTextureShader->SetInt("u_RenderedTexture", 0);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glDrawArrays(GL_TRIANGLES, 0, 6); // 2*3 indices starting at 0 -> 2 triangles

		glDisableVertexAttribArray(0);

		glDeleteBuffers(1, &quad_vertexbuffer);

	}

}