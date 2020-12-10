#include "SceneEditorCLR.h"
#include <Onyx/Scene/Scene.h>

using namespace System::Runtime::InteropServices;

namespace OnyxCLR {



	SceneEditorCLR::SceneEditorCLR(Onyx::EditorApplication* editor)
	{
		m_NativeSceneEditor = new Onyx::SceneEditor();

		//REGISTER THIS COMPONENT WITH ONYX ENGINE
		editor->InitEngineComponents(m_NativeSceneEditor);

	}

	SceneEditorCLR::~SceneEditorCLR()
	{

	}

	SceneCLR^ SceneEditorCLR::NewScene()
	{
		Onyx::SceneData sceneData = m_NativeSceneEditor->NewScene();

		SceneCLR^ result = gcnew SceneCLR();
		result->Name = gcnew System::String(sceneData.Name.c_str());
		result->FilePath = gcnew System::String(sceneData.FilePath.c_str());
		result->Indentifier = gcnew System::String(sceneData.Identifier.c_str());

		return result;
	}

	SceneCLR^ SceneEditorCLR::OpenScene(System::String^ filePath)
	{
		Onyx::SceneData sceneData = m_NativeSceneEditor->OpenScene((char*)Marshal::StringToHGlobalAnsi(filePath).ToPointer());

		SceneCLR^ result = gcnew SceneCLR();
		result->Name = gcnew System::String(sceneData.Name.c_str());
		result->FilePath = gcnew System::String(sceneData.FilePath.c_str());
		result->Indentifier = gcnew System::String(sceneData.Identifier.c_str());

		return result;
	}

	bool SceneEditorCLR::SaveScene(System::String^ filePath)
	{
		return m_NativeSceneEditor->SaveScene((char*)Marshal::StringToHGlobalAnsi(filePath).ToPointer());
	}

	static List<SceneNodeCLR^>^ IterateNode(Onyx::SceneNode* sceneNode)
	{
		List<SceneNodeCLR^>^ result = gcnew List<SceneNodeCLR^>();
		SceneNodeCLR^ node = gcnew SceneNodeCLR();
		node->Name = gcnew String(sceneNode->GetSceneNodeName().data());
		node->UUID = gcnew String(sceneNode->GetSceneNodeUuid().data());
		result->Add(node);

		//Recursively parse child nodes
		for (int i =0; i < sceneNode->GetChildren().size(); ++i)
		{
			result[0]->Nodes->AddRange(IterateNode(sceneNode->GetChildren()[i]));
		}

		return result;
	}

	SceneNodeCLR^ SceneEditorCLR::GetSceneGraphCLRTest()
	{
		Onyx::SceneNode* nativeSceneNode = m_NativeSceneEditor->GetScene()->GetSceneGraph();
		SceneNodeCLR^ result = gcnew SceneNodeCLR();

		result->Name = "SCENE_GRAPH_NODE";

		//Skip the actual scene entity as the return list acts as it
		//TODO
		for (auto var : nativeSceneNode->GetChildren())
		{
			result->Nodes->AddRange(IterateNode(var));
		}



		return result;

		
	}

	static uint32_t FindEntityBySceneNode(Onyx::SceneNode* sceneNode, const std::string& Guid)
	{
		uint32_t result = 0xFFFFFFFF;

		if (sceneNode->GetSceneNodeUuid() == Guid) {
			if (sceneNode->GetEntity() != nullptr) {
				result = sceneNode->GetEntity()->GetID();
				return result;
			}
		}
		else {
			for (int i = 0; i < sceneNode->GetChildren().size(); ++i)
			{
				result = (FindEntityBySceneNode(sceneNode->GetChildren()[i], Guid));
			}
		}
		return result;
	}


	uint32_t SceneEditorCLR::GetEntityFromSceneNode(System::String^ sceneNodeGuid)
	{
		std::string sceneNodeGuidStr = (char*)Marshal::StringToHGlobalAnsi(sceneNodeGuid).ToPointer();

		Onyx::SceneNode* nativeSceneNode = m_NativeSceneEditor->GetScene()->GetSceneGraph();

		for (auto var : nativeSceneNode->GetChildren())
		{
			uint32_t result =  FindEntityBySceneNode(var, sceneNodeGuidStr);
			if (result != 0xFFFFFFFF)
				return result;
		}

		return 0xFFFFFFFF;
	}

	static Onyx::Entity* FindEntityBySceneNodeTest(Onyx::SceneNode* sceneNode, const std::string& Guid)
	{
		Onyx::Entity* result = nullptr;

		if (sceneNode->GetSceneNodeUuid() == Guid) {
			if (sceneNode->GetEntity() != nullptr) {
				result = sceneNode->GetEntity();
				return result;
			}
		}
		else {
			for (int i = 0; i < sceneNode->GetChildren().size(); ++i)
			{
				result = (FindEntityBySceneNodeTest(sceneNode->GetChildren()[i], Guid));
			}
		}
		return result;
	}

	List<Component^>^ SceneEditorCLR::GetEntityComponents(System::String^ sceneNodeGuid)
	{
		std::string sceneNodeGuidStr = (char*)Marshal::StringToHGlobalAnsi(sceneNodeGuid).ToPointer();

		List<Component^>^ entityComponents = gcnew List<Component ^>();

		//Assuming ID is valid

		Onyx::SceneNode* sceneGraph = m_NativeSceneEditor->GetScene()->GetSceneGraph();

		Onyx::Entity* entity = FindEntityBySceneNodeTest(sceneGraph, sceneNodeGuidStr);

		if (entity) {

			if (entity->HasComponent<Onyx::TagComponent>()) {
				Onyx::TagComponent& t = entity->GetComponent<Onyx::TagComponent>();
				entityComponents->Add(gcnew TagComponent(gcnew System::String(t.Tag.c_str())));
			}

			if (entity->HasComponent<Onyx::TransformComponent>()) {
				Onyx::TransformComponent& t = entity->GetComponent<Onyx::TransformComponent>();
				
				Vector3^ position = gcnew Vector3(t.Position.x, t.Position.y, t.Position.z);
				Vector3^ rotation = gcnew Vector3(t.Rotation.x, t.Rotation.y, t.Rotation.z);
				Vector3^ scale = gcnew Vector3(t.Scale.x, t.Scale.y, t.Scale.z);

				entityComponents->Add(gcnew TransformComponent(position, rotation, scale));

			}
		}

		return entityComponents;
	}

}