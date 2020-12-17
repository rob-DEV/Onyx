#include "onyxpch.h"
#include "Gizmo.h"
#include <Onyx/Graphics/Shader.h>
#include <Onyx/Graphics/ModelLoader.h>
#include <Onyx/Graphics/RenderCommand.h>

#include <Onyx/Core/Input.h>

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>


namespace Onyx {

	GizmoData Gizmo::s_GizmoData = GizmoData();
	GizmoModelData Gizmo::s_GizmoModelData = GizmoModelData();
	RenderData Gizmo::s_RendererData = RenderData();

	void Gizmo::Init()
	{
		//Gizmo
		s_GizmoModelData.Transform = ModelLoader::Load("TransformModel", "res/models/transform/Transform.obj");
		s_GizmoModelData.Rotate = ModelLoader::Load("RotateModel", "res/models/transform/Rotation.obj");
		s_GizmoModelData.Scale = ModelLoader::Load("ScaleModel", "res/models/transform/Scale.obj");

		s_GizmoModelData.Active = s_GizmoModelData.Transform;
		SetState(GizmoState::TRANSFORM);

		//Renderer
		FramebufferSpecification fbSpec(1130, 636, 2, true);
		fbSpec.MultiSample = false;

		s_RendererData.Framebuffer = Framebuffer::Create(fbSpec);

		//Initialize Gizmo buffers
		s_RendererData.GizmoVAO = VertexArray::Create();
		s_RendererData.GizmoVBO = VertexBuffer::Create();
		s_RendererData.GizmoIBO = IndexBuffer::Create(10000);


		s_RendererData.GizmoVBO->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_VertColor" }
		});

		s_RendererData.GizmoVAO->AddVertexBuffer(s_RendererData.GizmoVBO);
		s_RendererData.GizmoVAO->SetIndexBuffer(s_RendererData.GizmoIBO);
		
		s_RendererData.MeshVertexBufferBase = new char[sizeof(GizmoVertex) * 10000];
		s_RendererData.MeshIndexBufferBase = new uint32_t[10000];
		s_RendererData.VertexCount = 0;
		s_RendererData.IndexCount = 0;

		ShaderCache::Add("GizmoShader", Shader::Create("res/shaders/GizmoShader.glsl"));

		glGenBuffers(2, s_RendererData.SelectionPixelBuffers);
		glBindBuffer(GL_PIXEL_PACK_BUFFER, s_RendererData.SelectionPixelBuffers[0]);
		glBufferData(GL_PIXEL_PACK_BUFFER, 1 * 1 * 4, 0, GL_STREAM_READ);
		glBindBuffer(GL_PIXEL_PACK_BUFFER, s_RendererData.SelectionPixelBuffers[1]);
		glBufferData(GL_PIXEL_PACK_BUFFER, 1 * 1 * 4, 0, GL_STREAM_READ);
		glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);

	}

	void Gizmo::SetState(GizmoState state)
	{
		if (state == GizmoState::TRANSFORM)
			s_GizmoModelData.Active = s_GizmoModelData.Transform;
		else if (state == GizmoState::ROTATE)
			s_GizmoModelData.Active = s_GizmoModelData.Rotate;
		else if (state == GizmoState::SCALE)
			s_GizmoModelData.Active = s_GizmoModelData.Scale;
	
		s_GizmoData.State = state;
	}

	GizmoState Gizmo::GetState()
	{
		return s_GizmoData.State;
	}


	static glm::vec2 mousePosition = glm::vec2(0.0f);
	static bool red = false;

	void Gizmo::Manipulate(Timestep ts, const Camera& camera, glm::mat4& modelTransform)
	{
		//Render
		s_RendererData.ViewProjectionMatrix = camera.GetViewProjectionMatrix();
		s_GizmoData.GizmoTransformMatrix = modelTransform;

		switch (s_GizmoData.State)
		{
		case GizmoState::TRANSFORM:
			s_GizmoModelData.Active = s_GizmoModelData.Transform;
			break;
		case GizmoState::ROTATE:
			s_GizmoModelData.Active = s_GizmoModelData.Rotate;
			break;
		case GizmoState::SCALE:
			s_GizmoModelData.Active = s_GizmoModelData.Scale;
			break;
		default:
			break;
		}

		Render();

		//Gizmo logic
		s_RendererData.Framebuffer->Bind();
		
		glm::vec2 mousePos = Input::GetMousePosition();
		
		if (Input::IsMouseButtonPressed(ONYX_MOUSE_BUTTON_1)) {

			if (s_GizmoData.Axis == AXIS::NONE) {
				//switch to selection buffer
				glReadBuffer(GL_COLOR_ATTACHMENT1);
				glBindBuffer(GL_PIXEL_PACK_BUFFER, s_RendererData.SelectionPixelBuffers[s_RendererData.PboIndex]);

				uint32_t x = (uint32_t)mousePos.x;
				uint32_t y = (uint32_t)(650.0f -mousePos.y);
				glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, 0);

				glBindBuffer(GL_PIXEL_PACK_BUFFER, s_RendererData.SelectionPixelBuffers[s_RendererData.PboNextIndex]);
				uint32_t* selectionBufferPtr = (uint32_t*)glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);

				//Copy to a more manageable structure 
				RGBA rgba;
				memcpy(&rgba, selectionBufferPtr, 4);

				glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
			
				printf("GIZMO RGBA COLOR 0x%1x, 0x%1x, 0x%1x, 0x%1x\n", rgba.R, rgba.G, rgba.B, rgba.A);

				//only set if no axis is bound
				if (rgba.R) {
					s_GizmoData.Axis = AXIS::X;
				}
				else if (rgba.G) {
					s_GizmoData.Axis = AXIS::Y;
				}
				else if (rgba.B) {
					s_GizmoData.Axis = AXIS::Z;
				}

			}
		}
		else {
			s_GizmoData.Axis = AXIS::NONE;
		}


		glm::vec2 mousePos1 = Input::GetMousePosition();
		float diffX = (mousePos1.x - mousePosition.x) * (mousePos1.x * 0.0001) * ts.GetMilliseconds();
		float diffY = (mousePos1.y - mousePosition.y)  * (mousePos1.y * 0.0001) * ts.GetMilliseconds();

		if (s_GizmoData.State == GizmoState::TRANSFORM) {
			switch (s_GizmoData.Axis) {
			case AXIS::X:
				modelTransform = glm::translate(modelTransform, glm::vec3(-diffX * 0.1f, 0, 0));
				break;
			case AXIS::Y:
				modelTransform = glm::translate(modelTransform, glm::vec3(0, -diffY * 0.1f, 0));
				break;
			case AXIS::Z:
				modelTransform = glm::translate(modelTransform, glm::vec3(0, 0, diffX * 0.1f));
				break;
			}
		}
		else if(s_GizmoData.State == GizmoState::ROTATE) {
			switch (s_GizmoData.Axis) {
			case AXIS::X:
				modelTransform = glm::rotate(modelTransform, diffX * 0.01f, glm::vec3(1.0f,0.0f,0.0f));
				break;
			case AXIS::Y:
				modelTransform = glm::rotate(modelTransform, -diffX * 0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
				break;
			case AXIS::Z:
				modelTransform = glm::rotate(modelTransform, diffX * 0.01f, glm::vec3(0.0f, 0.0f, 1.0f));
				break;
			}
		}
		else if (s_GizmoData.State == GizmoState::SCALE) {
			switch (s_GizmoData.Axis) {
			case AXIS::X:
				modelTransform = glm::scale(modelTransform, glm::vec3(1.0f + (-diffX * 0.01f), 1, 1));
				break;
			case AXIS::Y:
				modelTransform = glm::scale(modelTransform, glm::vec3(1, 1.0f + (-diffX * 0.01f), 1));
				break;
			case AXIS::Z:
				modelTransform = glm::scale(modelTransform, glm::vec3(1, 1, 1.0f + (-diffX * 0.01f)));
				break;
			}
		}


		mousePosition = mousePos1;
		
		s_RendererData.Framebuffer->Unbind();
	}

	void Gizmo::Render()
	{
		s_RendererData.VertexCount = 0;
		s_RendererData.IndexCount = 0;
		s_RendererData.MeshIndexBufferWritePtr = s_RendererData.MeshIndexBufferBase;
		s_RendererData.MeshVertexBufferWritePtr = s_RendererData.MeshVertexBufferBase;

		s_RendererData.Framebuffer->Bind();
		RenderCommand::SetClearColor({ 0.0, 0.0, 0.0, 0.0 });
		RenderCommand::Clear();

		//Render Gizmo
		Shader* meshShader = ShaderCache::Get("GizmoShader");
		meshShader->Bind();
		meshShader->SetMat4("u_ViewProjection", s_RendererData.ViewProjectionMatrix);
		s_RendererData.GizmoVAO->Bind();
		s_RendererData.GizmoVBO->Bind();
		s_RendererData.GizmoIBO->Bind();
	
		for (auto mesh : s_GizmoModelData.Active->GetMeshes()) {
			for (int i = 0; i < mesh.m_Vertices.size(); ++i) {
				((GizmoVertex*)s_RendererData.MeshVertexBufferWritePtr)->Position = s_GizmoData.GizmoTransformMatrix * glm::vec4(mesh.m_Vertices[i].Position, 1.0f);
				((GizmoVertex*)s_RendererData.MeshVertexBufferWritePtr)->Color = mesh.m_Material->GetColor(ColorParameterType::DIFFUSE);
				s_RendererData.MeshVertexBufferWritePtr = (char*)s_RendererData.MeshVertexBufferWritePtr + sizeof(GizmoVertex);
			}

			for (int i = 0; i < mesh.m_Indices.size(); ++i) {
				*s_RendererData.MeshIndexBufferWritePtr = mesh.m_Indices[i] + s_RendererData.VertexCount;
				s_RendererData.MeshIndexBufferWritePtr++;
			}

			s_RendererData.IndexCount += mesh.m_Indices.size();
			s_RendererData.VertexCount += mesh.m_Vertices.size();
		}

		unsigned long long vertexBufferSize = (unsigned char*)s_RendererData.MeshVertexBufferWritePtr - (unsigned char*)s_RendererData.MeshVertexBufferBase;

		if (vertexBufferSize != 0) {
			s_RendererData.GizmoVBO->SetData((void*)s_RendererData.MeshVertexBufferBase, vertexBufferSize);
			s_RendererData.GizmoIBO->SetData((void*)s_RendererData.MeshIndexBufferBase, s_RendererData.IndexCount);
		}

		if (s_RendererData.IndexCount > 0)
			RenderCommand::DrawIndexed(s_RendererData.GizmoVAO, s_RendererData.IndexCount);

		s_RendererData.Framebuffer->Unbind();

	}

}