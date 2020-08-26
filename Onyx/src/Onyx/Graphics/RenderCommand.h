#ifndef _ONYX_GRAPHICS_RENDERCOMMAND_H_
#define _ONYX_GRAPHICS_RENDERCOMMAND_H_

#include <Onyx/Core/Core.h>
#include <Onyx/Graphics/RendererAPI.h>
#include <Onyx/Graphics/VertexArray.h>

namespace Onyx {
	class ONYX_API RenderCommand {
	public:
		inline static void Init() { m_RendererAPI->Init(); }
		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { m_RendererAPI->SetViewport(x, y, width, height); }
		inline static void SetClearColour(const glm::vec4& color) { m_RendererAPI->SetClearColor(color); }
		inline static void Clear() { m_RendererAPI->Clear(); }
		inline static void DrawArrays(VertexArray* vertexArray, uint32_t count) { m_RendererAPI->DrawArrays(vertexArray, count); };
		inline static void DrawIndexed(VertexArray* vertexArray) { m_RendererAPI->DrawIndexed(vertexArray); };
		inline static void DrawIndexed(VertexArray* vertexArray, uint32_t indexCount) { m_RendererAPI->DrawIndexed(vertexArray, indexCount); };

		//EXPERIMENTAL
		inline static RenderedPixelData GetRenderedFrameBuffer() { return m_RendererAPI->GetRenderedFrameBuffer(); };

	private:
		static RendererAPI* m_RendererAPI;
		
	};
}



#endif // !_ONYX_GRAPHICS_RENDERCOMMAND_H_
