#ifndef _ONYX_GRAPHICS_BUFFER_H_
#define _ONYX_GRAPHICS_BUFFER_H_

#include <Onyx/core/Core.h>

typedef unsigned int uint32_t;

namespace Onyx {

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		static VertexBuffer* create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		virtual uint32_t getCount() const = 0;

		static IndexBuffer* create(uint32_t* indices, uint32_t size);
	};

}


#endif // !_ONYX_GRAPHICS_BUFFER_H_
