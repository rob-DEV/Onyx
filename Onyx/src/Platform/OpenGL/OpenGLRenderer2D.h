#ifndef _ONYX_PLATFORM_OPENGL_RENDERER2D_H_
#define _ONYX_PLATFORM_OPENGL_RENDERER2D_H_

#include <Onyx/Core/Core.h>
#include <Onyx/Graphics/Buffer.h>
#include <Onyx/Graphics/Shader.h>
#include <Onyx/Graphics/VertexArray.h>
#include <Onyx/Graphics/Renderer2D.h>
#include <Platform/OpenGL/OpenGLBuffer.h>
#include <Platform/OpenGL/OpenGLShader.h>
#include <Platform/OpenGL/OpenGLVertexArray.h>


#include <glm/glm.hpp>


namespace Onyx {

	struct Vertex2D;

	class OpenGLRenderer2D : public Renderer2D {
	public:
		virtual void initImplementation();
		virtual void destroyImplementation();

		virtual void beginSceneImplementation(const OrthographicCamera& camera);
		virtual void endSceneImplementation();

		virtual void drawQuadImplementation(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		virtual void drawQuadImplementation(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		virtual void drawQuadImplementation(const glm::vec3& position, const glm::vec2& size, Texture2D* texture);
		virtual void flushImplementation();

	private:
		OpenGLVertexArray* m_QuadVertexArray;
		OpenGLVertexBuffer* m_QuadVertexBuffer;
		OpenGLIndexBuffer* m_QuadIndexBuffer;
		uint32_t m_IndexCount = 0;

		OpenGLShader* m_QuadShader;

		//CPU mapped storage
		Vertex2D* m_QuadVertexBufferData;
		Vertex2D* m_QuadVertexBufferWritePtr;

	};

}

#endif // !_ONYX_GRAPHICS_RENDERER2D_H_