#include "Sandbox2D.h"
#include "Sandbox2DSecond.h"

#include <Onyx/Onyx.h>


class Sandbox : public Onyx::Application {

public:
	Sandbox() {

		m_LayerStack.push_back(new Sandbox2D);
		//m_LayerStack.push_back(new Sandbox2DSecond);

	}

	~Sandbox()
	{

	}
};



Onyx::Application* CreateApplication() {

	return new Sandbox();
}