#include "onyxpch.h"
#include "Mesh.h"


namespace Onyx {

	

	PrimitiveMesh::PrimitiveMesh(const std::vector<glm::vec3>* vertices, const std::vector<uint32_t>* indices) 
	{
		m_Vertices = vertices;
		m_Indices = indices;
		m_Color = glm::vec4(static_cast <float> (rand()) / static_cast <float> (RAND_MAX), static_cast <float> (rand()) / static_cast <float> (RAND_MAX), static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 1.0f);
		m_BaseColor = m_Color;
	}
	//PRIMITIVE MESH DATA

	//CUBE
	const std::vector<glm::vec3>* PrimitiveMesh::s_CubeVertices = new std::vector<glm::vec3>{
		// front
		{-0.5f, -0.5f,  0.5f},
		{0.5f, -0.5f,  0.5f},
		{0.5f,  0.5f,  0.5f},
		{-0.5f,  0.5f,  0.5f},
		// back
		{-0.5f, -0.5f, -0.5f},
		{0.5f, -0.5f, -0.5f},
		{0.5f,  0.5f, -0.5f},
		{-0.5f,  0.5f, -0.5f}
	};
	const std::vector<uint32_t>* PrimitiveMesh::s_CubeIndices = new std::vector<uint32_t>{
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

	//SPHERE
	const std::vector<glm::vec3>* PrimitiveMesh::s_SphereVertices = new std::vector<glm::vec3>{

	};
	const std::vector<uint32_t>* PrimitiveMesh::s_SphereIndices = new std::vector<uint32_t>{


	};

	//CONE
	const std::vector<glm::vec3>* PrimitiveMesh::s_ConeVertices = new std::vector<glm::vec3>{
		{0.000000f,-1.0f, -1.000000f },
		{0.195090f,-1.0f, -0.980785f },
		{0.382683f,-1.0f, -0.923880f },
		{0.555570f,-1.0f, -0.831470f },
		{0.707107f,-1.0f, -0.707107f },
		{0.831470f,-1.0f, -0.555570f },
		{0.923880f,-1.0f, -0.382683f },
		{0.980785f,-1.0f, -0.195090f },
		{1.000000f,-1.0f, -0.000000f },
		{0.980785f,-1.0f, 0.195090f },
		{0.923880f,-1.0f, 0.382683f },
		{0.831470f,-1.0f, 0.555570f },
		{0.707107f,-1.0f, 0.707107f },
		{0.555570f,-1.0f, 0.831470f },
		{0.382683f,-1.0f, 0.923880f },
		{0.195090f,-1.0f, 0.980785f },
		{-0.000000f, -1.0f, 1.000000f },
		{-0.195091f,-1.0f, 0.980785f},
		{-0.382684f,-1.0f, 0.923879f},
		{-0.555571f,-1.0f, 0.831469f},
		{-0.707107f,-1.0f, 0.707106f},
		{-0.831470f,-1.0f, 0.555570f},
		{-0.923880f,-1.0f, 0.382683f},
		{0.000000f, 1.0f, 0.000000f  },
		{-0.980785f, -1.0f, 0.195089f },
		{-1.000000f, -1.0f, -0.000001f},
		{-0.980785f, -1.0f, -0.195091f},
		{-0.923879f, -1.0f, -0.382684f},
		{-0.831469f, -1.0f, -0.555571f},
		{-0.707106f, -1.0f, -0.707108f},
		{-0.555569f, -1.0f, -0.831470f},
		{-0.382682f, -1.0f, -0.923880f},
		{-0.195089f, -1.0f, -0.980786f}
	};
	const std::vector<uint32_t>* PrimitiveMesh::s_ConeIndices = new std::vector<uint32_t>{

		0,
		23,
		1,
		1,
		23,
		2,
		2,
		23,
		3,
		3,
		23,
		4,
		4,
		23,
		5,
		5,
		23,
		6,
		6,
		23,
		7,
		7,
		23,
		8,
		8,
		23,
		9,
		9,
		23,
		10,
		10,
		23,
		11,
		11,
		23,
		12,
		12,
		23,
		13,
		13,
		23,
		14,
		14,
		23,
		15,
		15,
		23,
		16,
		16,
		23,
		17,
		17,
		23,
		18,
		18,
		23,
		19,
		19,
		23,
		20,
		20,
		23,
		21,
		21,
		23,
		22,
		22,
		23,
		24,
		24,
		23,
		25,
		25,
		23,
		26,
		26,
		23,
		27,
		27,
		23,
		28,
		28,
		23,
		29,
		29,
		23,
		30,
		30,
		23,
		31,
		31,
		23,
		32,
		32,
		23,
		0
	};

}
