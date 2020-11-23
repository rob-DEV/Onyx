#include "onyxpch.h"
#include "ModelLoader.h"

#include <Onyx/Core/FileIO.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Onyx {


	Model* ModelLoader::Load(const std::string& name, const std::string& path)
	{
		//Determine model type to load

		std::string ext = FileIO::GetFileExtension(path);

		if (ext != "obj" && ext != "fbx") {
			assert(false, "Unsupported model format!");
			return nullptr;
		}
		
		Model* result = ModelLoader::LoadModelFromFile(path);
		result->m_Name = name;

		return result;
	}


	Model* ModelLoader::LoadModelFromFile(const std::string& path)
	{
		printf("Loading model from : %s\n", path.c_str());

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path.c_str(), aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_GenUVCoords |
			aiProcess_SortByPType |
			aiProcess_RemoveRedundantMaterials |
			aiProcess_FindInvalidData |
			aiProcess_FlipUVs |
			aiProcess_CalcTangentSpace |
			aiProcess_GenSmoothNormals |
			aiProcess_ImproveCacheLocality |
			aiProcess_OptimizeMeshes |
			aiProcess_SplitLargeMeshes);


		// Check if scene is not null and model is done loading
		if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			std::cerr << "Assimp Error for " << path.c_str() << ": " << importer.GetErrorString() << '\n';
			importer.FreeScene();

			return false;
		}

		Model* result = new Model();

		processNode(scene->mRootNode, scene, result);

		importer.FreeScene();


		return result;
	}

	void ModelLoader::processNode(aiNode* node, const aiScene* scene, Model* result)
	{
		int nmesh = scene->mNumMeshes;

		for (size_t i = 0; i < nmesh; ++i) {
			result->AddMesh(processMesh(scene->mMeshes[i], scene));
		}
	}

	Mesh ModelLoader::processMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex3D> vertices;
		glm::vec3 min(0.001);
		glm::vec3 max(0.001);

		for (auto i = 0; i < mesh->mNumVertices; ++i) {
			Vertex3D vertex;

			if (mesh->HasPositions()) {
				vertex.Position.x = mesh->mVertices[i].x;
				vertex.Position.y = mesh->mVertices[i].y;
				vertex.Position.z = mesh->mVertices[i].z;

				// Construct bounding box
				if (vertex.Position.x < min.x) min.x = vertex.Position.x;
				if (vertex.Position.x > max.x) max.x = vertex.Position.x;

				if (vertex.Position.y < min.y) min.y = vertex.Position.y;
				if (vertex.Position.y > max.y) max.y = vertex.Position.y;

				if (vertex.Position.z < min.z) min.z = vertex.Position.z;
				if (vertex.Position.z > max.z) max.z = vertex.Position.z;

			}

			if (mesh->HasNormals()) {
				vertex.Normal.x = mesh->mNormals[i].x;
				vertex.Normal.y = mesh->mNormals[i].y;
				vertex.Normal.z = mesh->mNormals[i].z;
			}

			if (mesh->HasTangentsAndBitangents()) {
				vertex.Tangent.x = mesh->mTangents[i].x;
				vertex.Tangent.y = mesh->mTangents[i].y;
				vertex.Tangent.z = mesh->mTangents[i].z;
			}

			if (mesh->HasTextureCoords(0)) {
				// Just take the first set of texture coords (since we could have up to 8)
				vertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
				vertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
			}
			else {
				vertex.TexCoords = glm::vec2(0.0f);
			}
			vertex.Color = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
			vertices.push_back(vertex);
		}

	

		// Get indices from each face
		std::vector<uint32_t> indices;
		for (auto i = 0; i < mesh->mNumFaces; ++i) {
			const auto face = mesh->mFaces[i];
			for (auto j = 0; j < face.mNumIndices; ++j) {
				indices.emplace_back(face.mIndices[j]);
			}
		}

		
		return Mesh(vertices, indices);
	}

}