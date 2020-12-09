#ifndef _ONYX_SCENE_NODE_H_
#define _ONYX_SCENE_NODE_H_

#include <Onyx/Core/Core.h>
#include <Onyx/Entity/Entity.h>

#include <Onyx/Resources/UUID.h>

namespace Onyx {
	class SceneNode
	{
	public:

		SceneNode() :
			m_SceneNodeUuid(UUID::Generate(8)) {
			m_ChildNodes.reserve(10);
		}
		SceneNode(Entity* entity) :
			m_Entity(entity),
			m_SceneNodeUuid(UUID::Generate(8))
		{
			m_ChildNodes.reserve(10);
		}

		const std::string_view GetSceneNodeName() const { return m_SceneNodeName; };
		const std::string_view GetSceneNodeUuid() const { return m_SceneNodeUuid; };

		const SceneNode* GetParent() const { return m_ParentNode; };
		const std::vector<SceneNode*>& GetChildren() const { return m_ChildNodes; };

		void SetName(const std::string& name) {  m_SceneNodeName = name; };

		SceneNode* AddChild(SceneNode* node) { m_ChildNodes.push_back(node); return node; };
		
		Entity* GetEntity() const { return m_Entity; };

	private:
		std::string m_SceneNodeName = "NAME_PLACEHOLDER";
		std::string m_SceneNodeUuid = "00000000";

		//Scene Graph 1st node has no parent
		SceneNode* m_ParentNode = nullptr;
		std::vector<SceneNode*> m_ChildNodes = std::vector<SceneNode*>();
		Entity* m_Entity;
	};
}

#endif // !_ONYX_SCENE_NODE_H_