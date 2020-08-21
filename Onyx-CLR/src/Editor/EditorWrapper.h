#pragma once

#include <Onyx/OnyxEditor.h>

namespace OnyxCLR {

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


		void OpenScene(System::String^ filePath);
		void SaveScene(System::String^ filePath);

	private:
		//Example
		Onyx::Application* m_Application;
		void* m_CurrentScene;

	};

}

