#ifndef _ONYX_GRAPHICS_MESH_H_
#define _ONYX_GRAPHICS_MESH_H_

#include <Onyx/Core/Core.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>

namespace Onyx {

	class ONYX_API Mesh {
	public:
		
		const std::vector<glm::vec3>* m_Vertices;
		const std::vector<uint32_t>* m_Indices;

		//color test
		glm::vec4 m_Tint = { 1.0f,0.0f,0.85f, 1.0f };
		glm::vec4 m_BaseColor;
		glm::vec4 m_Color;

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

	enum class PrimitiveMeshType {
		Cube = 0,
		Sphere,
		Cone,
		Toroid
	};

	class ONYX_API PrimitiveMesh : public Mesh {
	public:

		PrimitiveMesh(const std::vector<glm::vec3>* vertices, const std::vector<uint32_t>* indices);

		static PrimitiveMesh* Create(PrimitiveMeshType primitive)
		{
			if (primitive == PrimitiveMeshType::Cube) {
				return new PrimitiveMesh(PrimitiveMesh::s_CubeVertices, PrimitiveMesh::s_CubeIndices);
			}

			if (primitive == PrimitiveMeshType::Sphere) {
				return new PrimitiveMesh(PrimitiveMesh::s_ConeVertices, PrimitiveMesh::s_ConeIndices);
			}

			if (primitive == PrimitiveMeshType::Cone) {
				return new PrimitiveMesh(PrimitiveMesh::s_ConeVertices, PrimitiveMesh::s_ConeIndices);
			}

			return nullptr;
		}

	private:
		//CUBE
		const static std::vector<glm::vec3>* s_CubeVertices;
		const static std::vector<uint32_t>* s_CubeIndices;

		//SPHERE
		const static std::vector<glm::vec3>* s_SphereVertices;
		const static std::vector<uint32_t>* s_SphereIndices;

		//CONE
		const static std::vector<glm::vec3>* s_ConeVertices;
		const static std::vector<uint32_t>* s_ConeIndices;

		

	};

}


#endif //_ONYX_GRAPHICS_MESH_H_
