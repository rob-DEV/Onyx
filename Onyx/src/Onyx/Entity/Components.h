#ifndef _ONYX_COMPONENTS_H_
#define _ONYX_COMPONENTS_H_

#include <Onyx/Core/Core.h>
#include <Onyx/Graphics/Mesh.h>


#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Onyx {

	struct ONYX_API TagComponent
	{
		TagComponent() = default;
		TagComponent(const TagComponent& other) = default;
		TagComponent(std::string_view tag) : Tag(tag) {}
		std::string Tag;
	};

	struct ONYX_API TransformComponent 
	{
		//PUBLIC CONSTRUCTOR
		TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = default;
		TransformComponent(const glm::vec3& position)
			: Position(position) {}

		glm::vec3 Position = glm::vec3(0.0f);
		glm::vec3 Scale = glm::vec3(1.0f);

	};

	struct ONYX_API MeshRendererComponent
	{
	public:
		MeshRendererComponent() = default;
		MeshRendererComponent(const MeshRendererComponent& other) = default;
		~MeshRendererComponent() = default;
		MeshRendererComponent(const std::vector<Mesh>& mesh) : Meshes(mesh) {}

		std::vector<Mesh> Meshes;
	};


}


#endif