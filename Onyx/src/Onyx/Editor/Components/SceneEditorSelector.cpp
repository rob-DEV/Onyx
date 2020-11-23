#include "onyxpch.h"
#include "SceneEditorSelector.h"

#include <Onyx/Core/Input.h>

#include <Onyx/Graphics/ModelLoader.h>
#include <Onyx/Editor/Components/SceneEditor.h>

#include <glad/glad.h>

namespace Onyx {

	SceneEditorSelector::SceneEditorSelector(SceneEditor* sceneEditor) :
		m_SceneEditor(sceneEditor)
	{

	}

	void SceneEditorSelector::OnUpdate()
	{
		if (Input::IsMouseButtonPressed(ONYX_MOUSE_BUTTON_1)) {

// 			glm::vec2 pos = Input::GetMousePosition();
// 			
// 
// 			uint32_t a = 0x00FFFFFF;
// 
// 			//Read from the selection buffer
// 			glReadBuffer(GL_COLOR_ATTACHMENT1);
// 			glReadPixels(pos.x, pos.y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &a);
// 
// 			printf("Selected Entity at pos %.3f,%.3f - %u\n", pos.x, pos.y, a);
// 
// 			m_SceneEditor->SetSelectedEntity(a);



		}


	}
}
