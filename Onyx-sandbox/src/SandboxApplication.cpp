#include <iostream>
#include <Onyx/Onyx.h>

class Sandbox : public Onyx::Application
{
public:

	Sandbox()
	{	

	}

	~Sandbox()
	{

	}

};

Onyx::Application* CreateApplication()
{
	return new Sandbox();
}