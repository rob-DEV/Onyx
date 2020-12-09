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

	List<OnyxCLR::Entity^>^ SceneEditorCLR::GetAllEntitiesTest()
	{
		List<OnyxCLR::Entity^>^ eList = gcnew List<OnyxCLR::Entity^>();

		for (auto e : m_NativeSceneEditor->GetAllEntitiesTest()) {

			Entity^ a = gcnew Entity();
			a->m_Entity = e->GetID();
			eList->Add(a);

		}

		return eList;
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

		//Skip the actually scene entity as the return list acts as it
		//TODO
		for (auto var : nativeSceneNode->GetChildren())
		{
			result->Nodes->AddRange(IterateNode(var));
		}



		return result;

		
	}

}