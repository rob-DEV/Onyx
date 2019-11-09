#include <iostream>


#include <Onyx/Onyx.h>
#include <Onyx/core/Window.h>
#include <Onyx/core/Input.h>
#include <Platform/Windows/WindowsWindow.h>
#include <Platform/OpenGL/OpenGLRendererAPI.h>

#include <glm/vec4.hpp>

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