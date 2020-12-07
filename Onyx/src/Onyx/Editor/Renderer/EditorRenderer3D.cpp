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

#include <Onyx/Core/Input.h>

namespace Onyx {

	EditorRendererData EditorRenderer3D::s_RendererData = EditorRendererData();

	void EditorRenderer3D::Init()
	{
		ShaderCache::Add("SkyboxEditor", Shader::Create("res/shaders/SkyboxEditor.glsl"));
		ShaderCache::Add("3DEditor", Shader::Create("res/shaders/3DEditor.glsl"));
		ShaderCache::Add("RenderTexture", Shader::Create("res/shaders/RenderTexture.glsl"));

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
		RenderCommand::Clear();

 		Shader* skyboxShader = ShaderCache::Get("SkyboxEditor");
 		skyboxShader->Bind();
 		skyboxShader->SetMat4("u_ViewProjection", s_RendererData.View);
 		scene->m_SkyBox->Draw();

		Shader* meshShader = ShaderCache::Get("3DEditor");
		meshShader->Bind();
		meshShader->SetMat4("u_ViewProjection", s_RendererData.WorldViewProjection);
		meshShader->SetFloat3("u_LightPosition", glm::vec3(1.256f, 8.0f, 0.1f));

		SceneNode* sceneGraphNode = scene->GetSceneGraph();
		
		for (auto entity : scene->m_Entities)
		{
			if (entity->IsStatic()) {
				//Check if not in static batch
				if (!s_RendererData.StaticBatch.IsInBatch(entity->GetID())) {
					if (entity->HasComponent<TransformComponent>() && entity->HasComponent<MeshRendererComponent>()) {
						TransformComponent& t = entity->GetComponent<TransformComponent>();
						MeshRendererComponent& mr = entity->GetComponent<MeshRendererComponent>();

						glm::mat4 transform = glm::translate(glm::mat4(1.0f), t.Position)
							* glm::scale(glm::mat4(1.0f), glm::vec3(0.01f));

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


		if (Input::IsMouseButtonPressed(ONYX_MOUSE_BUTTON_1)) {
			glm::vec2 mousePos = Input::GetMousePosition();

			uint32_t selectedPixel = 0xFFFFFFFF;

			//switch to selection buffer
			glReadBuffer(GL_COLOR_ATTACHMENT1);
			glBindBuffer(GL_PIXEL_PACK_BUFFER, s_RendererData.SelectionPixelBuffers[s_RendererData.PboIndex]);

			uint32_t x = (uint32_t)mousePos.x;
			uint32_t y = (uint32_t)(650.0f -mousePos.y);
			glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, 0);

			glBindBuffer(GL_PIXEL_PACK_BUFFER, s_RendererData.SelectionPixelBuffers[s_RendererData.PboNextIndex]);
			GLubyte* selectionBufferPtr = (GLubyte*)glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);

				uint32_t* p = (uint32_t*)selectionBufferPtr;
				selectedPixel = (uint32_t)(p[0]);
			
			printf("0x%8x\n", selectedPixel);

			glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
		}


		s_RendererData.Framebuffer->Unbind();

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
		glBindTexture(GL_TEXTURE_2D, s_RendererData.Framebuffer->GetColorAttachmentRendererID(selectedColorAttachment));
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