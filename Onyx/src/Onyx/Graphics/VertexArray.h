#ifndef _ONYX_GRAPHICS_VERTEXARRAY_H_
#define _ONYX_GRAPHICS_VERTEXARRAY_H_

#include "Buffer.h"
#include <vector>

namespace Onyx {

	class ONYX_API VertexArray {
	public:
		virtual ~VertexArray() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void addVertexBuffer(VertexBuffer* vertexBuffer) = 0;
		virtual void setIndexBuffer(IndexBuffer* indexBuffer) = 0;

		virtual const std::vector<VertexBuffer*>& getVertexBuffers() const = 0;
		virtual IndexBuffer* getIndexBuffer() const = 0;

		static VertexArray* create();
	};

}


#endif // !_ONYX_GRAPHICS_VERTEXARRAY_H_
