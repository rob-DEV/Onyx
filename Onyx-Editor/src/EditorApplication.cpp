#include <iostream>

#include <Onyx/Onyx.h>
#include "EditorLayer.h"

class Editor : public Onyx::Application {

public:
	Editor() {

		m_LayerStack.emplace_back(new EditorSandbox);

	}

	~Editor()
	{

	}
};

Onyx::Application* CreateApplication() {

	return new Editor();
}
int main(int argc, char** argv) {

	printf("--------------------------------------------------- Onyx Game Engine ---------------------------------------------------\n");

	Onyx::Application* onyxApplication = CreateApplication();
	onyxApplication->SetWindowTitle("Onyx Editor");
	onyxApplication->Run();
	delete onyxApplication;

	return 0;
}
