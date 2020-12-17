#include "onyxpch.h"
#include "ScreenRenderer.h"

#include <Onyx/Graphics/Shader.h>
#include <Onyx/Graphics/VertexArray.h>
#include <Onyx/Graphics/Framebuffer.h>
#include <Onyx/Graphics/RenderCommand.h>

#include <glad/glad.h>

namespace Onyx {

	ScreenRendererData ScreenRenderer::s_ScreenRendererData = ScreenRendererData();

	void ScreenRenderer::Init()
	{
		ShaderCache::Add("ScreenQuadShader", Shader::Create("res/shaders/RenderTexture.glsl"));
		s_ScreenRendererData.ScreenShader = ShaderCache::Get("ScreenQuadShader");

		s_ScreenRendererData.ScreenQuadVAO = VertexArray::Create();

		s_ScreenRendererData.ScreenQuadVBO = VertexBuffer::Create();
		s_ScreenRendererData.ScreenQuadVBO->SetLayout({
			{ ShaderDataType::Float3, "a_Position" }
			});

		const float vertexBufferData[] = {
			-1.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			-1.0f,  1.0f, 0.0f,
			-1.0f,  1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			1.0f,  1.0f, 0.0f,
		};
		s_ScreenRendererData.ScreenQuadVBO->SetData((float*)vertexBufferData, sizeof(vertexBufferData));

		s_ScreenRendererData.ScreenQuadVAO->AddVertexBuffer(s_ScreenRendererData.ScreenQuadVBO);

		FramebufferSpecification fbSpec = FramebufferSpecification(1130, 636, 1, true);
		fbSpec.MultiSample = false;

		s_ScreenRendererData.ResolvedTextureFrambuffer = Framebuffer::Create(fbSpec);
	}

	void ScreenRenderer::Destroy()
	{

	}

	void ScreenRenderer::RenderFramebufferTextureToScreen(Framebuffer* framebuffer, uint32_t attachmentIndex)
	{
		
		bool multisample = framebuffer->GetSpecification().MultiSample;

		uint32_t fbColorAttachment = 0;

		if (multisample) {
			//render to resolved FBO get texture
			framebuffer->ResolveToFramebuffer(s_ScreenRendererData.ResolvedTextureFrambuffer, attachmentIndex);
			fbColorAttachment = s_ScreenRendererData.ResolvedTextureFrambuffer->GetColorAttachmentRendererID(0);

		}
		else {
			fbColorAttachment = framebuffer->GetColorAttachmentRendererID(attachmentIndex);
		}
		
		//Draw framebuffer texture (resolved if fbo is multi sampled)

		s_ScreenRendererData.ScreenShader->Bind();
		s_ScreenRendererData.ScreenQuadVAO->Bind();
		s_ScreenRendererData.ScreenQuadVBO->Bind();

		glBindTextureUnit(0, fbColorAttachment);
		s_ScreenRendererData.ScreenShader->SetInt("u_RenderedTexture", 0);

		RenderCommand::DrawArrays(6);

	}

}