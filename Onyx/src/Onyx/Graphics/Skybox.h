#ifndef _ONYX_GRAPHICS_SKYBOX_H_
#define _ONYX_GRAPHICS_SKYBOX_H_

#include <Onyx/Core/Core.h>
#include <Onyx/Graphics/Texture.h>
#include <Onyx/Graphics/VertexArray.h>

namespace Onyx {

	class Cubemap;
	class Shader;


	class ONYX_API Skybox {
	public:
		Skybox();
		Skybox(std::vector<std::string_view> paths);
		void Draw();

	private:
		Cubemap* m_SkyboxTexture;
		VertexArray* m_SkyboxVAO;
		VertexBuffer* m_SkyboxVBO;
	};
}


#endif
