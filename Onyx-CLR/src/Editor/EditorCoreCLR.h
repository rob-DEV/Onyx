#pragma once

#include <Onyx/Editor/Core/EditorCore.h>
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

	public ref class EditorCoreCLR
	{

	public:

		EditorCoreCLR();

		~EditorCoreCLR();

		void Update();

		void UpdateEngineInput(
			array<System::Boolean>^ keys, 
			array<System::Boolean>^ mouseButtons, 
			System::Drawing::Point mousePosition);

		void GetRenderedFrame(int* buffer);

		SceneEditorCLR^ SceneEditorInstance;

	private:
		//Example
		Onyx::EditorCore* OnyxEditorInstance;

	};
}

