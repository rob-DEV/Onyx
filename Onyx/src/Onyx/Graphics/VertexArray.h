#ifndef _ONYX_GRAPHICS_VERTEXARRAY_H_
#define _ONYX_GRAPHICS_VERTEXARRAY_H_

#include "Buffer.h"
#include <vector>

namespace Onyx {

	class ONYX_API VertexArray {
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(VertexBuffer* vertexBuffer) = 0;
		virtual void SetIndexBuffer(IndexBuffer* indexBuffer) = 0;

		virtual const std::vector<VertexBuffer*>& GetVertexBuffers() const = 0;
		virtual IndexBuffer* GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};

}


#endif // !_ONYX_GRAPHICS_VERTEXARRAY_H_
