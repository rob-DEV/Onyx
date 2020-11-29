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
		std::string Name;
		std::string FilePath;
		std::string Identifier;
	};

	class ONYX_API Scene {
	public:
		Scene();
		Scene(const std::string& identifier);
		~Scene();

		Entity* CreateEntity();
		void OnUpdate(Timestep timestep);

	private:

		std::string m_SceneIdentifier;

		Registry m_EntityRegistry;

		std::vector<Entity*> m_Entities;

		Skybox* m_SkyBox;


		friend class Entity;
		friend class SceneEditor;
		friend class SceneSerializer;

		friend class Renderer3D;

	};
}

#endif