#ifndef _ONYX_MODEL_H_
#define _ONYX_MODEL_H_

#include <Onyx/Graphics/Mesh.h>

namespace Onyx {

	class Model
	{
	public:
		Model() = default;
		~Model() = default;

		void AddMesh(const Mesh& mesh) { m_Meshes.push_back(mesh); };
		const std::vector<Mesh>& GetMeshes() const { return m_Meshes; };
	
	private:
		std::string m_Name;
		std::vector<Mesh> m_Meshes;

		friend class ModelLoader;
	};
}

#endif

