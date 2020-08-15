#ifndef _ONYX_PLATFORM_OPENGL_BUFFER_H_
#define _ONYX_PLATFORM_OPENGL_BUFFER_H_

#include <Onyx/graphics/Buffer.h>

namespace Onyx {
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void SetData(void* data, uint32_t size) override;

	private:
		uint32_t m_RendererID;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t count);
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;
		virtual uint32_t GetCount() const { return m_Count; }
		virtual void SetData(void* data, uint32_t count);


	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};

}



#endif // !_ONYX_PLATFORM_OPENGL_BUFFER_H_
