#ifndef _ONYX_GRAPHICS_FRAMEBUFFER_H_
#define _ONYX_GRAPHICS_FRAMEBUFFER_H_

#include "Onyx/Core/Core.h"

namespace Onyx {

	struct FramebufferSpecification {
		uint32_t Width = 0, Height = 0;

		FramebufferSpecification(uint32_t width, uint32_t height)
		{
			Width = width;
			Height = height;
		}
	};

	class ONYX_API Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	
		virtual const FramebufferSpecification& GetSpecification() const = 0;


		static Framebuffer* Create(const FramebufferSpecification& specification);

	};

}

#endif // !_ONYX_GRAPHICS_FRAMEBUFFER_H_
