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
		TagComponent(const std::string& tag) : Tag(tag) {}
		TagComponent(const TagComponent& other) = default;
		std::string Tag;
	};

	struct ONYX_API TransformComponent 
	{
	public:
		//PUBLIC CONSTRUCTOR
		TransformComponent() = default;
		TransformComponent(const glm::vec3& position)
			: m_LocalPosition(std::move(position)) {}
		TransformComponent(const TransformComponent& other) = default;
		~TransformComponent() = default;

		//PROPERTIES
		inline const glm::vec3& GetLocalPosition() const { return m_LocalPosition; };
		inline const glm::quat& GetLocalRotation() const { return m_LocalRotation; };

		//METHODS
		inline void SetLocalPostion(const glm::vec3& position) { m_LocalPosition = position; }
		inline void SetLocalRotation(const glm::quat& rotation) { m_LocalRotation = rotation; }

	private:

		glm::mat4 m_LocalMatrix = glm::mat4(1.0f);
		glm::mat4 m_GlobalMatrix = glm::mat4(1.0f);
		glm::mat4 m_LocalMatrixInverse = glm::mat4(1.0f);
		glm::mat4 m_GlobalMatrixInverse = glm::mat4(1.0f);
		glm::vec3 m_LocalPosition = glm::vec3(0.0f);
		glm::vec3 m_GlobalPosition = glm::vec3(0.0f);
		glm::quat m_LocalRotation = glm::quat(1.0f, 0, 0, 0);
		glm::quat m_GlobalRotation = glm::quat(1.0f, 0, 0, 0);
		glm::vec3 m_LocalScale = glm::vec3(1.0f, 1.0f, 1.0f);

	};

	struct ONYX_API MeshRendererComponent
	{
	public:
		MeshRendererComponent() = default;
		MeshRendererComponent(Mesh* mesh) : m_Mesh(mesh) {}
		MeshRendererComponent(const MeshRendererComponent& other) = delete;
		~MeshRendererComponent() = default;

		Mesh* GetMesh() const { return m_Mesh; }

	private:
		Mesh* m_Mesh = nullptr;

	};


}


#endif