#include "onyxpch.h"
#include "ModelLoader.h"

#include <Onyx/Core/FileIO.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Onyx {


	Model* ModelLoader::LoadFromFile(const std::string& path)
	{
		//Determine model type to load

		std::string ext = FileIO::GetFileExtension(path);

		if (ext == "obj")
			return LoadObjFromFile(path);
		if (ext == "fbx")
			return LoadObjFromFile(path);


		assert(false, "Unsupported model format!");
		return nullptr;
	}

	Model* ModelLoader::LoadObjFromFile(const std::string& path)
	{
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(path.c_str(),
			aiProcess_Triangulate |
			aiProcess_GenSmoothNormals |
			aiProcess_FlipUVs);

		if (!scene)
		{
			std::cout << "Mesh load failed!: " << path << std::endl;
			assert(0 == 0);
			return nullptr;
		}

		Model* result = new Model();

		for (int x = 0; x < scene->mNumMeshes; ++x) {

			const aiMesh* model = scene->mMeshes[x];


			std::vector<glm::vec3> vertices;
			std::vector<uint32_t> indices;

			const aiVector3D aiZeroVector(0.0f, 0.0f, 0.0f);
			for (unsigned int i = 0; i < model->mNumVertices; i++)
			{
				const aiVector3D* pPos = &(model->mVertices[i]);
				const aiVector3D* pNormal = &(model->mNormals[i]);
				const aiVector3D* pTexCoord = model->HasTextureCoords(0) ? &(model->mTextureCoords[0][i]) : &aiZeroVector;

				glm::vec3 vert(pPos->x, pPos->y, pPos->z);

				vertices.push_back(vert);
			}

			for (unsigned int i = 0; i < model->mNumFaces; i++)
			{
				const aiFace& face = model->mFaces[i];
				assert(face.mNumIndices == 3);
				indices.push_back(face.mIndices[0]);
				indices.push_back(face.mIndices[1]);
				indices.push_back(face.mIndices[2]);
			}

			result->m_Meshes.push_back(new Mesh());
			result->m_Meshes.back()->m_Vertices = new std::vector<glm::vec3>(vertices);
			result->m_Meshes.back()->m_Indices = new std::vector<uint32_t>(indices);

		}



		return result;

	}

	Model* ModelLoader::LoadFbxFromFile(const std::string& path)
	{
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(path.c_str(),
			aiProcess_Triangulate |
			aiProcess_GenSmoothNormals |
			aiProcess_FlipUVs);

		if (!scene)
		{
			std::cout << "Mesh load failed!: " << path << std::endl;
			assert(0 == 0);
		}


		const aiMesh* model = scene->mMeshes[0];


		std::vector<glm::vec3> vertices;
		std::vector<uint32_t> indices;

		const aiVector3D aiZeroVector(0.0f, 0.0f, 0.0f);
		for (unsigned int i = 0; i < model->mNumVertices; i++)
		{
			const aiVector3D* pPos = &(model->mVertices[i]);
			const aiVector3D* pNormal = &(model->mNormals[i]);
			const aiVector3D* pTexCoord = model->HasTextureCoords(0) ? &(model->mTextureCoords[0][i]) : &aiZeroVector;

			glm::vec3 vert(pPos->x, pPos->y, pPos->z);

			vertices.push_back(vert);
		}

		for (unsigned int i = 0; i < model->mNumFaces; i++)
		{
			const aiFace& face = model->mFaces[i];
			assert(face.mNumIndices == 3);
			indices.push_back(face.mIndices[0]);
			indices.push_back(face.mIndices[1]);
			indices.push_back(face.mIndices[2]);
		}

		Model* result = new Model();
		result->m_Meshes.push_back(new Mesh());
		result->m_Meshes[0]->m_Vertices = new std::vector<glm::vec3>(vertices);
		result->m_Meshes[0]->m_Indices = new std::vector<uint32_t>(indices);


		return result;
	}

}