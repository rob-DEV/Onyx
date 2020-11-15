#pragma once

#include <Onyx/Editor/Editor.h>
#include "Bitmap/BitmapDirect.h"

namespace OnyxCLR {

	public ref class RenderedFramebufferPixels {
	public:
		array<System::Byte>^ Data;
		System::Int32 Size;

		System::Drawing::Bitmap^ Bitmap;
	};

	public ref class OnyxEditor
	{

	public:

		/// <summary>
		/// Constructors a Editor CLR Instance
		/// </summary>
		OnyxEditor();

		//Cleanup
		~OnyxEditor();

		void Update();

		void UpdateEngineInput(
			array<System::Boolean>^ keys, 
			array<System::Boolean>^ mouseButtons, 
			System::Drawing::Point mousePosition);

		void GetRenderedFrame(int* buffer);

		void OpenScene(System::String^ filePath);
		void SaveScene(System::String^ filePath);

		//testing
		void CreateEntity(float x, float y, float z);


	private:
		//Example
		Onyx::Editor* m_Editor;

	};
}

