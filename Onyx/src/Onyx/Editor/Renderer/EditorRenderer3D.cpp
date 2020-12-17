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
#include <Onyx/Graphics/RenderCommand.h>

#include <Onyx/Core/Input.h>
#include <Onyx/Editor/Components/SceneEditorSelector.h>


namespace Onyx {

	EditorRendererData EditorRenderer3D::s_RendererData = EditorRendererData();

	void EditorRenderer3D::Init()
	{
		ShaderCache::Add("SkyboxEditor", Shader::Create("res/shaders/SkyboxEditor.glsl"));
		ShaderCache::Add("3DEditor", Shader::Create("res/shaders/3DEditor.glsl"));
		
		s_RendererData.StaticBatch.SetBufferLayout({
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

		s_RendererData.Framebuffer = Framebuffer::Create(fbSpec);


		glGenBuffers(2, s_RendererData.SelectionPixelBuffers);
		glBindBuffer(GL_PIXEL_PACK_BUFFER, s_RendererData.SelectionPixelBuffers[0]);
		glBufferData(GL_PIXEL_PACK_BUFFER, 1 * 1 * 4, 0, GL_STREAM_READ);
		glBindBuffer(GL_PIXEL_PACK_BUFFER, s_RendererData.SelectionPixelBuffers[1]);
		glBufferData(GL_PIXEL_PACK_BUFFER, 1 * 1 * 4, 0, GL_STREAM_READ);
		glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);

	}

	void EditorRenderer3D::Shutdown()
	{

	}

	void EditorRenderer3D::BeginScene(const Camera& camera)
	{
		//NOTE: Casted to mat3 to wipe out position data for cube map
		s_RendererData.View = camera.GetProjectionMatrix() * glm::mat4(glm::mat3(camera.GetViewMatrix()));
		s_RendererData.WorldViewProjection = camera.GetViewProjectionMatrix();

		s_RendererData.StaticBatch.Begin();


	}

	void EditorRenderer3D::DrawScene(const Scene* scene)
	{
		//Bind Framebuffer
		s_RendererData.Framebuffer->Bind();
		RenderCommand::SetClearColor({ 0.2, 0.2, 0.2, 1.0 });
		RenderCommand::Clear();

 		Shader* skyboxShader = ShaderCache::Get("SkyboxEditor");
 		skyboxShader->Bind();
 		skyboxShader->SetMat4("u_ViewProjection", s_RendererData.View);
 		scene->m_SkyBox->Draw();

		Shader* meshShader = ShaderCache::Get("3DEditor");
		meshShader->Bind();
		meshShader->SetMat4("u_ViewProjection", s_RendererData.WorldViewProjection);
		meshShader->SetFloat3("u_LightPosition", glm::vec3(1.256f, 8.0f, 0.1f));

		for (auto entity : scene->m_Entities)
		{
			if (entity->IsStatic()) {
				//Check if not in static batch
				if (!s_RendererData.StaticBatch.IsInBatch(entity->GetID())) {
					if (entity->HasComponent<TransformComponent>() && entity->HasComponent<MeshRendererComponent>()) {
						TransformComponent& t = entity->GetComponent<TransformComponent>();
						MeshRendererComponent& mr = entity->GetComponent<MeshRendererComponent>();

						glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), t.Rotation.x, { 1, 0, 0 })
							* glm::rotate(glm::mat4(1.0f), t.Rotation.y, { 0, 1, 0 })
							* glm::rotate(glm::mat4(1.0f), t.Rotation.z, { 0, 0, 1 });

						glm::mat4 transform = glm::translate(glm::mat4(1.0f), t.Position)
							* rotation
							* glm::scale(glm::mat4(1.0f), glm::vec3(t.Scale));

						s_RendererData.StaticBatch.Submit(entity->GetID(), mr.Meshes, transform);
					}
				}
			}
		}
	
	}

	void EditorRenderer3D::EndScene()
	{
		
		static uint32_t selectedColorAttachment = 0;

		if (Input::IsKeyPressed(ONYX_KEY_L)) {
			selectedColorAttachment = (selectedColorAttachment + 1) % 2;
		}

		s_RendererData.StaticBatch.End();


		//test render selection buffer to PBO and get pixel value
		s_RendererData.PboIndex = (s_RendererData.PboIndex + 1) % 2;
		s_RendererData.PboNextIndex = (s_RendererData.PboIndex + 1) % 2;


		s_RendererData.Framebuffer->Unbind();

	}

}