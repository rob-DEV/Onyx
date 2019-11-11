#ifndef _ONYX_GRAPHICS_RENDERER_API_H_
#define _ONYX_GRAPHICS_RENDERER_API_H_

#include <Onyx/core/Core.h>
#include <glm/vec4.hpp>


namespace Onyx {

	class ONYX_API RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1, Vulkan = 2,
		};
	public:
		virtual ~RendererAPI() = default;
		virtual void init() = 0;
		virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void setClearColor(const glm::vec4& color) = 0;
		virtual void clear() = 0;

		inline static API getAPI() { return s_API; }

	private:
		static API s_API;
	};


}

#endif // !_ONYX_GRAPHICS_RENDERER_API_H_
