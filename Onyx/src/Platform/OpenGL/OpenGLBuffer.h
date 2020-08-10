#ifndef _ONYX_PLATFORM_OPENGL_BUFFER_H_
#define _ONYX_PLATFORM_OPENGL_BUFFER_H_

#include <Onyx/graphics/Buffer.h>

namespace Onyx {
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void bind() const override;
		virtual void unbind() const override;
		virtual void setData(void* data, uint32_t size) override;

	private:
		uint32_t m_RendererID;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t count);
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void bind() const;
		virtual void unbind() const;

		virtual uint32_t getCount() const { return m_Count; }
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};

}



#endif // !_ONYX_PLATFORM_OPENGL_BUFFER_H_
