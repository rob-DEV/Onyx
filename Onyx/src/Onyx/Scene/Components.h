#ifndef _ONYX_COMPONENTS_H_
#define _ONYX_COMPONENTS_H_

#include <Onyx/Core/Core.h>
#include <Onyx/Graphics/Mesh.h>


#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Onyx {

	struct ONYX_API Transform 
	{
	public:
		//PUBLIC CONSTRUCTOR
		Transform(const Transform& other) = default;

		//PROPERTIES
		inline const glm::vec3& GetLocalPosition() const { return m_LocalPosition; };
		inline const glm::quat& GetLocalRotation() const { return m_LocalRotation; };

		//METHODS
		inline void SetLocalPostion(const glm::vec3& position) { m_LocalPosition = position; }
		inline void SetLocalRotation(const glm::quat& rotation) { m_LocalRotation = rotation; }

	private:
		//PRIVATE CONSTRUCTOR - Accessible from Entity
		Transform() = default;
		Transform(const glm::vec3& position) 
			: m_LocalPosition(position) {}

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

	struct ONYX_API MeshRenderer
	{
	public:
		MeshRenderer() = default;
		MeshRenderer(const MeshRenderer& other) = default;
		const Mesh& GetMesh() const { return *m_Mesh; }

	private:
		MeshRenderer();
		Mesh* m_Mesh = nullptr;

	};


}


#endif