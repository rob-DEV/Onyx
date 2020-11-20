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

		virtual const FramebufferSpecification& GetProperties() const override { return m_Specification; }
	private:
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachments[2] = { 0,0 };
		uint32_t m_DepthAttachments[2] = { 0,0 };

		FramebufferSpecification m_Specification;
	};

}


#endif // !_ONYX_PLATFORM_OPENGL_FRAMEBUFFER_H_