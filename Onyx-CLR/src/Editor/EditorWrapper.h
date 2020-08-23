#pragma once

#include <Onyx/Editor/Editor.h>

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

		//Initialize Application in an editor context
		//Initialize GLFW renderer to off-screen
		//Setup OpenGL bitmap and framing
		//Initialize command to engine mechanism
		OnyxEditor();

		//Cleanup
		~OnyxEditor();

		void Update();
		array<System::Byte>^ GetRenderedFrame();

		void OpenScene(System::String^ filePath);
		void SaveScene(System::String^ filePath);

	private:
		//Example
		Onyx::Editor* m_Editor;
		System::Drawing::Bitmap^ m_RenderedFrame;
		//void* m_CurrentScene;

	};

}

