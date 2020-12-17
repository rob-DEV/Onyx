#ifndef _ONYX_SCREEN_RENDERER_H_
#define _ONYX_SCREEN_RENDERER_H_

#include <Onyx/Core/Core.h>


namespace Onyx {

	class Framebuffer;
	class VertexArray;
	class VertexBuffer;
	class Shader;

	struct ScreenRendererData {
		VertexArray* ScreenQuadVAO;
		VertexBuffer* ScreenQuadVBO;
		Shader* ScreenShader;

		Framebuffer* ResolvedTextureFrambuffer;
	};

	class ScreenRenderer
	{
	public:
		static void Init();
		static void Destroy();

		static void RenderFramebufferTextureToScreen(Framebuffer* framebuffer, uint32_t attachmentIndex);
	
	private:
		static ScreenRendererData s_ScreenRendererData;

	};

}

#endif // !_ONYX_SCREEN_RENDERER_H_