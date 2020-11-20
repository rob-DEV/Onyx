#include "onyxpch.h"
#include "SceneEditorSelector.h"

//EDITOR RAY TESTING
#include <Onyx/Core/Input.h>
#include <Onyx/Physics/Ray.h>

#include <Onyx/Model/ModelLoader.h>
#include <Onyx/Graphics/Renderer3D.h>

namespace Onyx {

	SceneEditorSelector::SceneEditorSelector(FirstPersonCameraController* editorCamera) :
		m_EditorCamera(editorCamera)
	{

	}

	void SceneEditorSelector::OnUpdate()
	{
		if (Input::IsMouseButtonPressed(ONYX_MOUSE_BUTTON_1)) {

			glm::vec2 pos = Input::GetMousePosition();
			printf("Mouse pos %.3f,%.3f\n", pos.x, pos.y);
		}


	}
}
