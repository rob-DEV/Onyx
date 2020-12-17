#ifndef _ONYX_PLATFORM_OPENGL_FRAMEBUFFER_H_
#define _ONYX_PLATFORM_OPENGL_FRAMEBUFFER_H_

#include <Onyx/Graphics/Framebuffer.h>


namespace Onyx {

	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& specification);
		virtual ~OpenGLFramebuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void BiltToScreen() const override;
		virtual void ResolveToFramebuffer(Framebuffer* framebuffer, uint32_t attachmentIndex) const override;

		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }

		virtual uint32_t GetColorAttachmentRendererID(uint32_t attachmentIndex) const override;

	private:
		static const uint32_t MAX_ATTACHMENT_COUNT = 32;
		
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachments[MAX_ATTACHMENT_COUNT];
		uint32_t m_DepthAttachments[MAX_ATTACHMENT_COUNT];

		FramebufferSpecification m_Specification;
	};

}


#endif // !_ONYX_PLATFORM_OPENGL_FRAMEBUFFER_H_