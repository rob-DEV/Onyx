#ifndef _ONYX_GRAPHICS_RENDERER_API_H_
#define _ONYX_GRAPHICS_RENDERER_API_H_

#include <Onyx/core/Core.h>
#include <Onyx/Graphics/VertexArray.h>

#include <glm/vec4.hpp>

namespace Onyx {

	//EXPERIMENTAL
	struct ONYX_API RenderedPixelData {

		char* Data;
		uint32_t Size;
		//NumberOfChannels?

		RenderedPixelData(void* data, uint32_t size) {
			Data = (char*)data;
			Size = 0;
		}
		RenderedPixelData(RenderedPixelData& other) {

			//Avoid multiple deletions on assignment
			Data = other.Data;
			other.Data = nullptr;
			Size = other.Size;

		}

		~RenderedPixelData() { 
			
			printf("%x", Data);
			
			//delete[] Data;
		}

		RenderedPixelData operator=(RenderedPixelData other) {
			Data = other.Data;
			other.Data = nullptr;
			Size = other.Size;
			return *this;
		}

	};


	class ONYX_API RendererAPI
	{
	public:
		enum class API	{	None = 0, OpenGL = 1, Vulkan = 2	};

		virtual ~RendererAPI() = default;
		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexed(VertexArray* vertexArray) = 0;
		virtual void DrawIndexed(VertexArray* vertexArray, uint32_t indexCount) = 0;

		////EXPERIMENTAL
		virtual RenderedPixelData GetRenderedFrameBuffer() = 0;


		inline static API GetAPI() { return s_API; }
		inline static bool VsyncEnabled() { return s_Vsync; };
		inline static RendererAPI* Create();

	private:
		static API s_API;
		static bool s_Vsync;
	};


}

#endif // !_ONYX_GRAPHICS_RENDERER_API_H_
