#include "onyxpch.h"
#include "OpenGLFramebuffer.h"

#include <glad/glad.h>

namespace Onyx {

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& specification)
		: m_Specification(specification)
	{
		memset(m_ColorAttachments, 0, sizeof(uint32_t) * MAX_ATTACHMENT_COUNT);
		memset(m_DepthAttachments, 0, sizeof(uint32_t) * MAX_ATTACHMENT_COUNT);

		if (m_Specification.AttachmentCount > 32)
			ONYX_ERROR("OpenGLFramebuffer ERROR: Framebuffer Attachment count cannot exceed MAX_FRAMEBUFFER_COUNT");
		
		//Generate Framebuffer
		glGenFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		if (m_Specification.MultiSample) {
			glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE, m_Specification.AttachmentCount, m_ColorAttachments);

			if (m_Specification.HasDepth)
				glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE, m_Specification.AttachmentCount, m_DepthAttachments);
		}
		else {
			glCreateTextures(GL_TEXTURE_2D, m_Specification.AttachmentCount, m_ColorAttachments);

			if (m_Specification.HasDepth)
				glCreateTextures(GL_TEXTURE_2D, m_Specification.AttachmentCount, m_DepthAttachments);
		}

		for (size_t i = 0; i < m_Specification.AttachmentCount; ++i) {

			if (m_Specification.MultiSample) {
				//Multi-sample
				glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_ColorAttachments[i]);

				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, m_Specification.Samples, GL_RGBA, m_Specification.Width, m_Specification.Height, GL_FALSE);

// 				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// 				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D_MULTISAMPLE, m_ColorAttachments[i], 0);

				if (m_Specification.HasDepth) {
					//Create depth textures
					glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_DepthAttachments[i]);

					glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, m_Specification.Samples, GL_RGBA, m_Specification.Width, m_Specification.Height, GL_FALSE);

					glTexStorage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, m_Specification.Samples, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height, GL_FALSE);
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE, m_DepthAttachments[i], 0);

				}

			}
			else {
				//Regular non - multi-sampled framebuffer
				//Create color buffers
				glBindTexture(GL_TEXTURE_2D, m_ColorAttachments[i]);

				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Specification.Width, m_Specification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_ColorAttachments[i], 0);

				if (m_Specification.HasDepth) {
					//Create depth textures
					glBindTexture(GL_TEXTURE_2D, m_DepthAttachments[i]);

					glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height);
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachments[i], 0);

				}
			}

		}
		GLuint buffers[]{ GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
		glDrawBuffers(2, buffers);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
	}

	void OpenGLFramebuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, m_Specification.Width, m_Specification.Height);
	}

	void OpenGLFramebuffer::Unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::BiltToScreen() const
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glDrawBuffer(GL_BACK);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_RendererID);
		glBlitFramebuffer(0, 0, m_Specification.Width, m_Specification.Height, 0, 0, m_Specification.Width, m_Specification.Height, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	}

	void OpenGLFramebuffer::ResolveToFramebuffer(Framebuffer* framebuffer, uint32_t attachmentIndex) const
	{
		//check color attachment
		OpenGLFramebuffer* fbo = (OpenGLFramebuffer*)framebuffer;
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo->m_RendererID);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, this->m_RendererID);

		//bind color attachment to read buffer
		glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);

		glBlitFramebuffer(0, 0, m_Specification.Width, m_Specification.Height, 0, 0,
			fbo->m_Specification.Width, fbo->m_Specification.Height,
			GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	uint32_t OpenGLFramebuffer::GetColorAttachmentRendererID(uint32_t colorAttachment) const
	{
		if (colorAttachment > m_Specification.AttachmentCount - 1)
			ONYX_ERROR("OpenGLFramebuffer ERROR: Specified color attachment exceeds specification attachment count!");

		return m_ColorAttachments[colorAttachment];
	}




}