#ifndef _ONYX_GRAPHICS_RENDERCOMMAND_H_
#define _ONYX_GRAPHICS_RENDERCOMMAND_H_

#include <Onyx/Core/Core.h>
#include <Onyx/Graphics/RendererAPI.h>
#include <Onyx/Graphics/VertexArray.h>

namespace Onyx {
	class ONYX_API RenderCommand {
	public:
		inline static void DrawIndexed(VertexArray* vertexArray) { m_RendererAPI->DrawIndexed(vertexArray); };
		inline static void DrawIndexed(VertexArray* vertexArray, uint32_t indexCount) { m_RendererAPI->DrawIndexed(vertexArray, indexCount); };
	private:
		static RendererAPI* m_RendererAPI;
		
	};
}



#endif // !_ONYX_GRAPHICS_RENDERCOMMAND_H_
