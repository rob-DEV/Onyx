#ifndef _ONYX_MODEL_LOADER_H_
#define _ONYX_MODEL_LOADER_H_

#include <Onyx/Core/Core.h>
#include <Onyx/Graphics/Model.h>
#include <Onyx/Graphics/Mesh.h>

struct aiScene;
struct aiNode;
struct aiMesh;

namespace Onyx {

	class ONYX_API ModelLoader {
	public:
		static Model* Load(const std::string& name, const std::string& path);

	private:
		static Model* LoadModelFromFile(const std::string& path);

		static void processNode(aiNode* node, const aiScene* scene, Model* result);
		static Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	};
}

#endif