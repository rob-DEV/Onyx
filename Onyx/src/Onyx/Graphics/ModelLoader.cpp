#include "onyxpch.h"
#include "ModelLoader.h"

#include <Onyx/Core/FileIO.h>
#include <Onyx/Resources/MaterialCache.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Onyx {


	Model* ModelLoader::Load(std::string_view name, std::string_view path)
	{
		//Determine model type to load

		std::string ext = FileIO::GetFileExtension(path.data());

		if (ext != "obj" && ext != "fbx") {
			assert(false, "Unsupported model format!");
			return nullptr;
		}
		
		Model* result = ModelLoader::LoadModelFromFile(path);
		result->m_Name = name;

		return result;
	}


	Model* ModelLoader::LoadModelFromFile(std::string_view path)
	{
		printf("Loading model from : %s\n", path.data());

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path.data(), aiProcess_Triangulate |
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
			aiProcess_SplitLargeMeshes
			);


		// Check if scene is not null and model is done loading
		if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			std::cerr << "Assimp Error for " << path.data() << ": " << importer.GetErrorString() << '\n';
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
		int nMeshes = scene->mNumMeshes;

		for (size_t i = 0; i < nMeshes; ++i) {
			result->AddMesh(processMesh(scene->mMeshes[i], scene));
		}
	}

	Mesh ModelLoader::processMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex3D> vertices;
		glm::vec3 min(0.001);
		glm::vec3 max(0.001);

		for (size_t i = 0; i < mesh->mNumVertices; ++i) {
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
		for (size_t i = 0; i < mesh->mNumFaces; ++i) {
			const auto face = mesh->mFaces[i];
			for (size_t j = 0; j < face.mNumIndices; ++j) {
				indices.emplace_back(face.mIndices[j]);
			}
		}

		Material* materialResult = nullptr;
		Material material;

		//Material test
		if (true /*REFACTOR TO LOAD MATERIAL*/) {
			if (mesh->mMaterialIndex >= 0) {

				const auto* mat = scene->mMaterials[mesh->mMaterialIndex];

				if (mat->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
					aiString name;
					mat->Get(AI_MATKEY_NAME, name);
					
					//Check if material already exists in the cache
					if (MaterialCache::Get().Exists(name.C_Str())) {
						materialResult = MaterialCache::Get().GetMaterial(name.C_Str());
					}
					else {
						//Not already loaded, load and cache
						aiString diffusePath;
						mat->GetTexture(aiTextureType_AMBIENT, 0, &diffusePath);

						std::string fullPath = std::string("res/models/Sponza/") + std::string(diffusePath.C_Str());

						material.AddTexture(TextureParameterType::DIFFUSE, fullPath);
						material.AddTexture(TextureParameterType::SPECULAR, fullPath);
						material.SetName(name.C_Str());
						//Add to MaterialCache
						materialResult = MaterialCache::Get().CacheMaterial(name.C_Str(), material);

					}
				}
				else {
					std::cout << "No texture image being imported " << std::endl;
				}
				

				
			}
		}

		if(materialResult == nullptr)
		{
			material = Material("NOT_SPECIFIED");
			materialResult = MaterialCache::Get().CacheMaterial("NOT_SPECIFIED", material);
		}

		return Mesh(vertices, indices, materialResult);
	}

}