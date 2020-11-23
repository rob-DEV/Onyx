#include "pch.h"
#include <Onyx/Graphics/RendererAPI.h>
#include <Onyx/Core/Keycodes.h>

#include <Onyx/Editor/Core/EditorInput.h>
#include <Onyx/Editor/Components/SceneEditor.h>

#include "EditorApplicationCLR.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Runtime::InteropServices;


#include <glm/glm.hpp>

namespace OnyxCLR {

	EditorApplicationCLR::EditorApplicationCLR()
	{
		OnyxEditorInstance = new Onyx::EditorApplication();
		
		SceneEditorInstance = gcnew OnyxCLR::SceneEditorCLR(OnyxEditorInstance);
	}

	EditorApplicationCLR::~EditorApplicationCLR()
	{
		
	}

	void EditorApplicationCLR::Update()
	{
		OnyxEditorInstance->OnUpdate();
	}


	void EditorApplicationCLR::UpdateEngineInput(array<System::Boolean>^ keys, array<System::Boolean>^ mouseButtons, System::Drawing::Point mousePosition)
	{
		for (size_t i = 0; i < 350; ++i)
			OnyxEditorInstance->GetInputKeyBuffer()[i] = keys[i];
		
		for (size_t i = 0; i < 8; ++i)
			OnyxEditorInstance->GetInputMouseButtonBuffer()[i] = mouseButtons[i];

		OnyxEditorInstance->SetMousePosition(mousePosition.X, mousePosition.Y);
	}

	void EditorApplicationCLR::GetRenderedFrame(int* buffer)
	{
		Onyx::RenderedPixelData dd = OnyxEditorInstance->GetRenderedFrame();

		int pos = 0;
		for (int i = 0; i < 1280 * 720; ++i)
		{
			buffer[i] = (255 << 24) + ((unsigned char)dd.Data[pos] << 16) + ((unsigned char)dd.Data[pos + 1] << 8) + (unsigned char)dd.Data[pos + 2];
			pos += 3;
		}
	}
}