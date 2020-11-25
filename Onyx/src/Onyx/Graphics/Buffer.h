#ifndef _ONYX_GRAPHICS_BUFFER_H_
#define _ONYX_GRAPHICS_BUFFER_H_

#include <Onyx/core/Core.h>

#include <cassert>
#include <iterator>
#include <initializer_list>

namespace Onyx {

	class BufferLayout {};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetData(void* data, uint32_t size) = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static VertexBuffer* Create();
		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;
		virtual void SetData(void* data, uint32_t count) = 0;


		static IndexBuffer* Create(uint32_t count);
		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};

}


#endif // !_ONYX_GRAPHICS_BUFFER_H_
