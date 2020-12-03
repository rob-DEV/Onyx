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
		delete OnyxEditorInstance;
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

		OnyxEditorInstance->SetMousePosition((float)mousePosition.X, (float)mousePosition.Y);
	}

	System::IntPtr^ EditorApplicationCLR::GetNativeWindowHandle()
	{
		return gcnew System::IntPtr(OnyxEditorInstance->GetNativeWindowHandle());
	}

}