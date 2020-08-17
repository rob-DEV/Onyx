#include "onyxpch.h"
#include "Mesh.h"

#include <fbx/fbxsdk.h>

namespace Onyx {

	Mesh::Mesh(const std::vector<glm::vec3>* vertices, const std::vector<uint32_t>* indices)
		: m_Vertices(vertices), m_Indices(indices), m_Color(static_cast <float> (rand()) / static_cast <float> (RAND_MAX), static_cast <float> (rand()) / static_cast <float> (RAND_MAX), static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 1.0f)
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

		fbxsdk::FbxManager* manager = fbxsdk::FbxManager::Create();

		fbxsdk::FbxIOSettings* ioSettings = fbxsdk::FbxIOSettings::Create(manager, IOSROOT);
		manager->SetIOSettings(ioSettings);

		FbxImporter* importer = FbxImporter::Create(manager, "");
		importer->Initialize(path.c_str());

		FbxScene* scene = FbxScene::Create(manager, "tempScene");

		importer->Import(scene);
		importer->Destroy();

		FbxNode* rootNode = scene->GetRootNode();
		assert(rootNode, "RootNode not found!");

		std::vector<glm::vec3>* vertices = new std::vector<glm::vec3>();
		std::vector<int32_t>* indices = new std::vector<int32_t>();

		int numChildNodes = rootNode->GetChildCount();
		FbxNode* childNode = nullptr;

		uint32_t vertexCount = 0;
		uint32_t indexCount = 0;

		for (int i = 0; i < numChildNodes; i++)
		{
			childNode = rootNode->GetChild(i);
			fbxsdk::FbxMesh* mesh = childNode->GetMesh();

			if (mesh != nullptr) {
				//Loop mesh - pull vertices and indices
				int numVertices = mesh->GetControlPointsCount();
				
				for (int j = 0; j < numVertices; j++)
				{
					FbxVector4 vert = mesh->GetControlPointAt(j);
					vertices->emplace_back(glm::vec3((float)vert.mData[0], (float)vert.mData[1], (float)vert.mData[2]));
				}
				
				int numIndices = mesh->GetPolygonVertexCount();
				int* ptrIndices = mesh->GetPolygonVertices();

				//check if indices are triangular or quad indexed
				//covert to triangular if needed
				bool indexed = false;

				float ratio = (float)numIndices / (float)numVertices;
				if (ratio != 3) {

					for (int i = 0; i < numIndices; i++)
					{
						indices->push_back(ptrIndices[i] + indexCount);

					}
					indexCount += numIndices;

					indexed = true;
				}
				

				if (ratio == 3) {

					for (int i = 0; i < numIndices; i += 4) {

						int32_t zero = *ptrIndices++;
						int32_t one = *ptrIndices++;
						int32_t two = *ptrIndices++;
						int32_t three = *ptrIndices++;

						indices->push_back(zero + indexCount);
						indices->push_back(one + indexCount);
						indices->push_back(two + indexCount);

						indices->push_back(two + indexCount);
						indices->push_back(three + indexCount);
						indices->push_back(one + indexCount);

						indexCount += 6;
					}
					indexed = true;
				}

				assert(indexed, "Mesh index format not supported!");
			}

		}



		
		return new Mesh(vertices, (std::vector<uint32_t>*)indices);

	}

	Mesh* Mesh::Create(PrimitiveMeshType primitive)
	{
		if (primitive == PrimitiveMeshType::Cube) {
			return new Mesh(PrimitiveMesh::s_CubeVertices, PrimitiveMesh::s_CubeIndices);
		}

		if (primitive == PrimitiveMeshType::Sphere) {
			return new Mesh(PrimitiveMesh::s_ConeVertices, PrimitiveMesh::s_ConeIndices);
		}

		if (primitive == PrimitiveMeshType::Cone) {
			return new Mesh(PrimitiveMesh::s_ConeVertices, PrimitiveMesh::s_ConeIndices);
		}

		return nullptr;
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
