#include <iostream>

#include <Onyx/Onyx.h>
#include "EditorLayer.h"

class Editor : public Onyx::Application {

public:
	Editor(bool hidden) : Application(hidden) {

		m_LayerStack.emplace_back(new EditorSandbox);

	}

	~Editor()
	{

	}
};

Onyx::Application* CreateApplication() {

	return new Editor(true);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	printf("--------------------------------------------------- Onyx Editor ---------------------------------------------------\n");

	auto onyxApplication = CreateApplication();

	onyxApplication->Run();

	delete onyxApplication;


}
