#include "onyxpch.h"
#include "Mesh.h"



namespace Onyx {

	Mesh::Mesh(const std::vector<Vertex3D>& vertices, const std::vector<uint32_t>& indices)
	{
		m_Vertices = vertices;
		m_Indices = indices;
	}

	Mesh::Mesh(const std::vector<Vertex3D>& vertices, const std::vector<uint32_t>& indices, Material* material)
	{
		m_Vertices = vertices;
		m_Indices = indices;
		m_Material = material;
	}

	Mesh::~Mesh()
	{

	}

}
