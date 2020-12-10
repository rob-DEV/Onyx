#pragma once

#include <Onyx/Editor/Core/EditorApplication.h>
#include <Onyx/Editor/Components/SceneEditor.h>

#include <Entity/Entity.h>

#include "SceneCLR.h"
#include "SceneNodeCLR.h"
#include "../Entity\Components.h"

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

		SceneNodeCLR^ GetSceneGraphCLRTest();
		uint32_t GetEntityFromSceneNode(System::String^ sceneNodeGuid);

		List<Component^>^ GetEntityComponents(System::String^ sceneNodeGuid);


	private:
		Onyx::SceneEditor* m_NativeSceneEditor;

	};

}