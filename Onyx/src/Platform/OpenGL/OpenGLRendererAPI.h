#ifndef _ONYX_PLATFORM_OPENGL_RENDERER_API_H_
#define _ONYX_PLATFORM_OPENGL_RENDERER_API_H_

#include <Onyx/Graphics/RendererAPI.h>
#include <Onyx/Graphics/VertexArray.h>

namespace Onyx {
	class OpenGLRendererAPI : public RendererAPI {
	public:

		void Init();
		void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		void SetClearColor(const glm::vec4& color);
		void Clear();
		void DrawIndexed(VertexArray* vertexArray);
		void DrawIndexed(VertexArray* vertexArray, uint32_t indexCount);


	};
}




#endif // !_ONYX_PLATFORM_OPENGL_RENDERER_API_H_
