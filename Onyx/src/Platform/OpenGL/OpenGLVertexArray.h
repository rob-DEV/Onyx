#ifndef _ONYX_PLATFORM_OPENGL_VERTEXARRAY_H_
#define _ONYX_PLATFORM_OPENGL_VERTEXARRAY_H_

#include <Onyx/graphics/VertexArray.h>



namespace Onyx {


	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		void bind() const;
		void unbind() const;

		void addVertexBuffer(VertexBuffer* vertexBuffer);
		void setIndexBuffer(IndexBuffer* indexBuffer);

		const std::vector<VertexBuffer*>& getVertexBuffers() const { return m_VertexBuffers; };
		IndexBuffer* getIndexBuffer() const { return m_IndexBuffer; };

	private:
		uint32_t m_RendererID;
		uint32_t m_VertexBufferIndex = 0;
		std::vector<VertexBuffer*> m_VertexBuffers;
		IndexBuffer* m_IndexBuffer;

	};

}


#endif // !_ONYX_PLATFORM_OPENGL_VERTEXARRAY_H_

