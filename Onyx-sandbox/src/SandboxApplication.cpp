#include "Sandbox2D.h"

#include <Onyx/Onyx.h>


class Sandbox : public Onyx::Application {

public:
	Sandbox() {

		m_LayerStack.push_back(new Sandbox2D);

	}

	~Sandbox()
	{

	}
};



Onyx::Application* CreateApplication() {

	return new Sandbox();
}