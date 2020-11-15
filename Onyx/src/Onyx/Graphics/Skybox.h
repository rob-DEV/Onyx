#ifndef _ONYX_GRAPHICS_SKYBOX_H_
#define _ONYX_GRAPHICS_SKYBOX_H_

#include <Onyx/Core/Core.h>

#include <vector>
#include <string>
#include <glm/glm.hpp>

namespace Onyx {

	class Cubemap;
	class Shader;

	class ONYX_API Skybox {
	public:
		Skybox(std::vector<std::string> paths);
		Shader* GetShader() const { return m_Shader; }
		const std::vector<glm::vec3>& GetVertices() const { return m_SkyboxVertices; }
	private:
		Shader* m_Shader;
		Cubemap* m_SkyboxTexture;
		const static std::vector<glm::vec3> m_SkyboxVertices;

		

	};


}


#endif
