#ifndef _ONYX_SCENE_H_
#define _ONYX_SCENE_H_

#include <Onyx/Core/Core.h>
#include <Onyx/Core/TimeStep.h>

#include <Onyx/Graphics/Skybox.h>

#include <Onyx/Entity/Entity.h>
#include <Onyx/Entity/Registry.h>

namespace Onyx {

	class Entity;
	class Model;
	class Gizmo;
	
	struct SceneData {
		SceneData() = default;
		SceneData(std::string_view name, std::string_view filePath, std::string_view identifier) :
			Name(name),
			FilePath(filePath),
			Identifier(identifier)
		{

		}
		std::string Name;
		std::string FilePath;
		std::string Identifier;
	};

	class ONYX_API Scene {
	public:
		Scene();
		Scene(const SceneData& sceneData);
		~Scene();

		Entity* CreateEntity();
		void OnUpdate(Timestep timestep);

	private:
		SceneData m_SceneData;

		Registry m_EntityRegistry;
		std::vector<Entity*> m_Entities;

		Skybox* m_SkyBox;

		friend class Entity;
		friend class SceneEditor;
		friend class SceneSerializer;

		friend class Renderer3D;
		friend class EditorRenderer3D;
	};
}

#endif