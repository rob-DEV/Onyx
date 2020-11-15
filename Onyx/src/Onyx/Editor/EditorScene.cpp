#include "onyxpch.h"
#include "EditorScene.h"

#include <Onyx/Camera/FirstPersonCameraController.h>

namespace Onyx {



	EditorScene::EditorScene() : m_EditorSceneCamera(new FirstPersonCameraController())
	{

	}

	EditorScene::~EditorScene()
	{

	}

}