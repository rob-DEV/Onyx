#include "onyxpch.h"
#include "Mesh.h"

namespace Onyx {


	Mesh::Mesh(const std::vector<glm::vec3>* vertices, const std::vector<uint32_t>* indices)
		: m_Vertices(vertices), m_Indices(indices)
	{

	}

	Mesh::~Mesh()
	{

	}


	Mesh::Mesh(const std::string& path)
	{

	}

	Mesh* Mesh::Create(const std::string& path)
	{
		return nullptr;
	}

	Mesh* Mesh::Create(PrimitiveMeshType primitive)
	{
		if (primitive == PrimitiveMeshType::Cube) {
			return new Mesh(PrimitiveMesh::s_CubeVertices, PrimitiveMesh::s_CubeIndices);
		}

		return nullptr;
	}

	//PRIMITIVE MESH DATA
	const std::vector<glm::vec3>* PrimitiveMesh::s_CubeVertices = new std::vector<glm::vec3>{
		// front
		glm::vec3(-0.5f, -0.5f,  0.5f),
		glm::vec3(0.5f, -0.5f,  0.5f),
		glm::vec3(0.5f,  0.5f,  0.5f),
		glm::vec3(-0.5f,  0.5f,  0.5f),
		// back
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(0.5f,  0.5f, -0.5f),
		glm::vec3(-0.5f,  0.5f, -0.5f)
	};


	const std::vector<uint32_t>* PrimitiveMesh::s_CubeIndices = new std::vector<uint32_t> {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3

	};

}
