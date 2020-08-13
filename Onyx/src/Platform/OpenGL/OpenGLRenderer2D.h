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


namespace Onyx {

	struct Vertex2D;

	class OpenGLRenderer2D : public Renderer2D {
	private:
		virtual void InitImplementation();
		virtual void DestroyImplementation();

		virtual void BeginSceneImplementation(const OrthographicCamera& camera);
		virtual void EndSceneImplementation();
		virtual void FlushImplementation();


		virtual void DrawQuadImplementation(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		virtual void DrawQuadImplementation(const glm::vec3& position, const glm::vec2& size, Texture2D* texture);

		virtual void DrawRotatedQuadImplementation(const glm::vec3& position, float angle, const glm::vec3& ax, const glm::vec2& size, const glm::vec4& color);
		virtual void DrawRotatedQuadImplementation(const glm::vec3& position, float angle, const glm::vec3& ax, const glm::vec2& size, Texture2D* texture);

		virtual void DrawQuadImplementation(const glm::mat4& transform, const glm::vec4& color);
		virtual void DrawQuadImplementation(const glm::mat4& transform, Texture2D* texture);

	private:

		//CONSTANT
		static const uint32_t MAX_TEXTURE_SLOTS = 32;
		
		static const uint32_t MAX_QUADS = 100000;
		static const uint32_t MAX_QUADS_PER_DRAWCALL = 10000;
		static const uint32_t MAX_VERTICES_PER_DRAWCALL = MAX_QUADS_PER_DRAWCALL * 4;
		static const uint32_t MAX_INDICIES_PER_DRAWCALL = MAX_QUADS_PER_DRAWCALL * 6;


		Texture2D* m_WhiteTexture;
		std::array<Texture2D*, MAX_TEXTURE_SLOTS> m_TextureSlots;
		uint32_t m_TextureSlotIndex = 1; // 0 = white texture

		glm::vec4 m_QuadVertexPositions[4];

		OpenGLVertexArray* m_QuadVertexArray;
		OpenGLVertexBuffer* m_QuadVertexBuffer;
		OpenGLIndexBuffer* m_QuadIndexBuffer;

		uint32_t m_IndexCount = 0;
		uint32_t m_QuadCount = 0;

		OpenGLShader* m_QuadShader;

		//CPU mapped storage
		Vertex2D* m_QuadVertexBufferData;
		Vertex2D* m_QuadVertexBufferWritePtr;

		//Stats
		uint32_t m_DrawCalls = 0;
		uint32_t m_DrawnQuads = 0;

		

	};

}

#endif // !_ONYX_GRAPHICS_RENDERER2D_H_