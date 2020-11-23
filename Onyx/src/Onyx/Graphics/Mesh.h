#ifndef _ONYX_GRAPHICS_MESH_H_
#define _ONYX_GRAPHICS_MESH_H_

#include <Onyx/Core/Core.h>

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "Vertex.h"
#include "Material.h"

namespace Onyx {

	class ONYX_API Mesh {
	public:
		
		Mesh(const std::vector<Vertex3D>& vertices, const std::vector<uint32_t>& indices);
		Mesh(const std::vector<Vertex3D>& vertices, const std::vector<uint32_t>& indices, const Material& material);


		std::vector<Vertex3D> m_Vertices;
		std::vector<uint32_t> m_Indices;

		Material m_Material;

	};

}


#endif //_ONYX_GRAPHICS_MESH_H_
