#include "onyxpch.h"
#include "OpenGLGraphicsContext.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>

namespace Onyx {



	OpenGLGraphicsContext::OpenGLGraphicsContext(GLFWwindow* window)
	{
		m_WindowHandle = window;
	}

	void OpenGLGraphicsContext::init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			printf("Failed to initialize GLAD\n");

		printf("OpenGL Info:\n");
		printf("  Vendor: %s\n", glGetString(GL_VENDOR));
		printf("  Renderer: %s\n", glGetString(GL_RENDERER));
		printf("  Version: %s\n", glGetString(GL_VERSION));


	}

	void OpenGLGraphicsContext::swapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}

