#include "onyxpch.h"
#include "OpenGLFramebuffer.h"

#include <glad/glad.h>

namespace Onyx {

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& specification)
		: m_Specification(specification)
	{
		if (m_RendererID)
		{
			glDeleteFramebuffers(1, &m_RendererID);
		}

		glGenFramebuffers(1, &m_RendererID);

		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		glCreateTextures(GL_TEXTURE_2D, 2, m_ColorAttachments);
		glCreateTextures(GL_TEXTURE_2D, 2, m_DepthAttachments);
		
		for (int i = 0; i < 2; ++i)
		{
			glBindTexture(GL_TEXTURE_2D, m_ColorAttachments[i]);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_Specification.Width, m_Specification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_ColorAttachments[i], 0);

			glBindTexture(GL_TEXTURE_2D, m_DepthAttachments[i]);

			glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachments[i], 0);
		}


		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
			printf("Framebuffer Complete!\n");
		}
		else {
			printf("Framebuffer Incomplete!\n");
		}
		
		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
	}

	void OpenGLFramebuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
	}

	void OpenGLFramebuffer::Unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}




}