#ifndef _ONYX_GRAPHICS_MESH_H_
#define _ONYX_GRAPHICS_MESH_H_

#include <Onyx/Core/Core.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>

namespace Onyx {

	enum class PrimitiveMeshType {
		Cube = 0,
		Sphere,
		Cone,
		Toroid
	};

	class ONYX_API Mesh {
	public:

		virtual ~Mesh();

		const std::vector<glm::vec3>& GetVertices() const { return *m_Vertices; };
		const std::vector<uint32_t>& GetIndices() const { return *m_Indices; };
		const std::vector<uint32_t>& GetNormals() const { return *m_Indices; };

		glm::vec4 Color;

	protected:
		Mesh(const std::vector<glm::vec3>* vertices, const std::vector<uint32_t>* indices);
		Mesh(const std::string& path);

	public:
		static Mesh* Create(const std::string& path);

		//primitive create, default - cube, sphere, cone
		static Mesh* Create(PrimitiveMeshType primitive);

	private:
		const std::vector<glm::vec3>* m_Vertices;
		const std::vector<uint32_t>* m_Indices;


	};


	class PrimitiveMesh : public Mesh {

		//CUBE
		const static std::vector<glm::vec3>* s_CubeVertices;
		const static std::vector<uint32_t>* s_CubeIndices;

		//SPHERE
		const static std::vector<glm::vec3>* s_SphereVertices;
		const static std::vector<uint32_t>* s_SphereIndices;

		//CONE


		//TORIOD

		friend class Mesh;
	};


}


#endif //_ONYX_GRAPHICS_MESH_H_
