#include "Sandbox2D.h"
#include "Sandbox3D.h"

#include <Onyx/Onyx.h>


class Sandbox : public Onyx::Application {

public:
	Sandbox() {

		m_LayerStack.push_back(new Sandbox2D);
		m_LayerStack.push_back(new Sandbox3D);

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

	onyxApplication->Run();
	delete onyxApplication;

	return 0;
}
