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
		TagComponent(const std::string& tag) : Tag(tag) {}
		std::string Tag;
	};

	struct ONYX_API TransformComponent 
	{
	public:
		//PUBLIC CONSTRUCTOR
		TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = default;
		TransformComponent(const glm::vec3& position)
			: m_LocalPosition(position) {}

		operator glm::mat4& () { return m_LocalMatrix; }
		operator const glm::mat4& () const { return m_LocalMatrix; }

		//PROPERTIES
		inline const glm::vec3& GetLocalPosition() const { return m_LocalPosition; };
		inline const glm::quat& GetLocalRotation() const { return m_LocalRotation; };
		inline const glm::vec3& GetScale() const { return m_LocalScale; };

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
		MeshRendererComponent(const MeshRendererComponent& other) = default;
		~MeshRendererComponent() = default;
		MeshRendererComponent(Mesh* mesh) : m_Mesh(mesh) {}

		Mesh* GetMesh() const { return m_Mesh; }

	private:
		Mesh* m_Mesh = nullptr;

	};


}


#endif