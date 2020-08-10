#ifndef _ONYX_PLATFORM_OPENGL_TEXTURE_2D_H_
#define _ONYX_PLATFORM_OPENGL_TEXTURE_2D_H_

#include <Onyx/Graphics/Texture.h>
#include <glad/glad.h>

namespace Onyx {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t getWidth() const override { return m_Width; }
		virtual uint32_t getHeight() const override { return m_Height; }

		virtual void setData(void* data, uint32_t size) override;
		virtual void bind(uint32_t slot = 0) const override;

	private:
		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		GLenum m_InternalFormat, m_DataFormat;
	};

}


#endif // !_ONYX_PLATFORM_OPENGL_TEXTURE_2D_H_
