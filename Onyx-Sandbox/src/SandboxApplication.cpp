#include "Sandbox2D.h"
#include "Sandbox3D.h"

#include <Onyx/Onyx.h>


class Sandbox : public Onyx::Application {

public:
	Sandbox() {

		m_LayerStack.emplace_back(new Sandbox3D);
		//m_LayerStack.emplace_back(new Sandbox2D);

	}

	~Sandbox()
	{

	}
};



Onyx::Application* CreateApplication() {

	return new Sandbox();
}

int main(int argc, char** argv) {

	printf("--------------------------------------------------- Onyx Game Engine ---------------------------------------------------\n");

	Onyx::Application* onyxApplication = CreateApplication();
	//onyxApplication->SetWindowTitle("Onyx : Sandbox3D");
	onyxApplication->Run();
	delete onyxApplication;

	return 0;
}
