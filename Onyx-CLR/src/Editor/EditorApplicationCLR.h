#pragma once

#include <Onyx/Editor/Core/EditorApplication.h>
#include <Bitmap/BitmapDirect.h>

#include "SceneEditorCLR.h"

using namespace System::Collections::Generic;

namespace OnyxCLR {

	public ref class RenderedFramebufferPixels {
	public:
		array<System::Byte>^ Data;
		System::Int32 Size;

		System::Drawing::Bitmap^ Bitmap;
	};

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

		void GetRenderedFrame(int* buffer);

		SceneEditorCLR^ SceneEditorInstance;

	private:
		//Example
		Onyx::EditorApplication* OnyxEditorInstance;

	};
}

