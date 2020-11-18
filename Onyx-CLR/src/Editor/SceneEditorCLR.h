#pragma once

#include <Onyx/Editor/Core/EditorCore.h>
#include <Onyx/Editor/Components/SceneEditor.h>

#include <Entity/Entity.h>

using namespace System::Collections::Generic;

namespace OnyxCLR {

	public ref class SceneEditorCLR
	{

	public:
		SceneEditorCLR(Onyx::EditorCore* editor);
		~SceneEditorCLR();

		void OpenScene(System::String^ filePath);
		void SaveScene(System::String^ filePath);

		List<OnyxCLR::Entity^>^ GetAllEntitiesTest();

	private:
		Onyx::SceneEditor* m_NativeSceneEditor;

	};

}