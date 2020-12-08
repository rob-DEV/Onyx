#ifndef _ONYX_SCENE_NODE_H_
#define _ONYX_SCENE_NODE_H_

#include <Onyx/Core/Core.h>
#include <Onyx/Entity/Entity.h>

namespace Onyx {
	class SceneNode
	{
	public:

		SceneNode() {
			m_ChildNodes.reserve(10);
		}
		SceneNode(Entity* entity) :
			m_Entity(entity)
		{
			m_ChildNodes.reserve(10);
		}

		Entity* GetEntity() const { return m_Entity; };
		const std::string_view GetName() const { return m_Name; };
		void SetName(const std::string& name) {  m_Name = name; };

		const std::vector<SceneNode*>& GetChildren() const { return m_ChildNodes; };
		const SceneNode* GetParent() const { return m_ParentNode; };

		SceneNode* AddChild(SceneNode* node) { m_ChildNodes.push_back(node); return node; };

	private:
		std::string m_Name = "NAME_PLACEHOLDER";

		//Scene Graph 1st node has no parent
		SceneNode* m_ParentNode = nullptr;
		std::vector<SceneNode*> m_ChildNodes = std::vector<SceneNode*>();
		Entity* m_Entity;
	};
}

#endif // !_ONYX_SCENE_NODE_H_