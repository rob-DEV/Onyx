#ifndef _ONYX_GRAPHICS_MESH_H_
#define _ONYX_GRAPHICS_MESH_H_

#include <Onyx/Core/Core.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>

namespace Onyx {

	class ONYX_API Mesh {
	public:
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> texCoord;
		std::vector<glm::vec3> normals;
		
		std::vector<uint32_t> vertexIndices;
		std::vector<uint32_t> texCoordIndices;
		std::vector<uint32_t> normalIndices;


	};

	class ONYX_API InternalMesh {
	public:
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> texCoord;
		std::vector<glm::vec3> normals;

		std::vector<uint32_t> vertexIndices;
		std::vector<uint32_t> texCoordIndices;
		std::vector<uint32_t> normalIndices;


	};
}


#endif //_ONYX_GRAPHICS_MESH_H_
