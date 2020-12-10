#include "onyxpch.h"
#include "Gizmo.h"
#include <Onyx/Graphics/Shader.h>
#include <Onyx/Graphics/ModelLoader.h>
#include <Onyx/Graphics/RenderCommand.h>

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

		//Renderer
		FramebufferSpecification fbSpec(1130, 636, 2, true);
		fbSpec.MultiSample = true;
		fbSpec.Samples = 4;

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

	void Gizmo::Manipulate(const Camera& camera, const glm::mat4& modelTransform)
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


	}

	void Gizmo::Render()
	{
		s_RendererData.VertexCount = 0;
		s_RendererData.IndexCount = 0;
		s_RendererData.MeshIndexBufferWritePtr = s_RendererData.MeshIndexBufferBase;
		s_RendererData.MeshVertexBufferWritePtr = s_RendererData.MeshVertexBufferBase;

		s_RendererData.Framebuffer->Bind();
		RenderCommand::SetClearColor({ 1.0, 1.0, 1.0, 1.0 });
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