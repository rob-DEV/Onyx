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

	class ONYX_API Mesh 
	{
	public:

		virtual ~Mesh();

		const std::vector<glm::vec3>& GetVertices() const { return *m_Vertices; };
		const std::vector<uint32_t>& GetIndices() const { return *m_Indices; };
		const std::vector<uint32_t>& GetNormals() const { return *m_Indices; };
		const glm::vec4& GetTintColor() const { return m_Color; };

		void SetTintColor(const glm::vec4& color) { m_Color = color; };
		void Select(bool isSelected);

	public:
		Mesh(const std::vector<glm::vec3>* vertices, const std::vector<uint32_t>* indices);
		Mesh(const std::string& path);

	public:
		static Mesh* Create(const std::string& path);

		//primitive create, default - cube, sphere, cone
		static Mesh* Create(PrimitiveMeshType primitive);

	private:
		const std::vector<glm::vec3>* m_Vertices;
		const std::vector<uint32_t>* m_Indices;

		//color test
		glm::vec4 m_Tint = { 1.0f,0.0f,0.85f, 1.0f };
		glm::vec4 m_BaseColor;
		glm::vec4 m_Color;

		//normals
	
		//material




	};


	struct PrimitiveMesh {
		
		//CUBE
		const static std::vector<glm::vec3>* s_CubeVertices;
		const static std::vector<uint32_t>* s_CubeIndices;

		//SPHERE
		const static std::vector<glm::vec3>* s_SphereVertices;
		const static std::vector<uint32_t>* s_SphereIndices;

		//CONE
		const static std::vector<glm::vec3>* s_ConeVertices;
		const static std::vector<uint32_t>* s_ConeIndices;

		//TORIOD

	};


}


#endif //_ONYX_GRAPHICS_MESH_H_
