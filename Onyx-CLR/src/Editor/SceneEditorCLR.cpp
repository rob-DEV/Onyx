#include "SceneEditorCLR.h"

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

	void SceneEditorCLR::OpenScene(System::String^ filePath)
	{
		m_NativeSceneEditor->OpenScene((char*)Marshal::StringToHGlobalAnsi(filePath).ToPointer());
	}

	void SceneEditorCLR::SaveScene(System::String^ filePath)
	{

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

}