#pragma once

#include <Onyx/Editor/Core/EditorApplication.h>
#include <Onyx/Editor/Components/SceneEditor.h>

#include <Entity/Entity.h>

#include "SceneCLR.h"

using namespace System::Collections::Generic;

namespace OnyxCLR {

	public ref class SceneEditorCLR
	{

	public:
		SceneEditorCLR(Onyx::EditorApplication* editor);
		~SceneEditorCLR();

		SceneCLR^ NewScene();
		SceneCLR^ OpenScene(System::String^ filePath);
		bool SaveScene(System::String^ filePath);

		List<OnyxCLR::Entity^>^ GetAllEntitiesTest();

	private:
		Onyx::SceneEditor* m_NativeSceneEditor;

	};

}