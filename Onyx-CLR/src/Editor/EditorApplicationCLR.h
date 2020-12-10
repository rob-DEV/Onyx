#pragma once

#include <Onyx/Editor/Core/EditorApplication.h>
#include "SceneEditorCLR.h"

using namespace System::Collections::Generic;

namespace OnyxCLR {

	public ref class EditorApplicationCLR
	{

	public:

		EditorApplicationCLR();

		~EditorApplicationCLR();

		void Update();

		void UpdateEngineInput(
			array<System::Boolean>^ keys, 
			array<System::Boolean>^ mouseButtons, 
			System::Drawing::Point mousePosition);

		System::IntPtr^ GetNativeWindowHandle();

		SceneEditorCLR^ SceneEditorInstance;

	private:
		//Example
		Onyx::EditorApplication* OnyxEditorInstance;

	};
}

