#include "onyxpch.h"
#include "OpenGLGraphicsContext.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>

namespace Onyx {

	void GLAPIENTRY DebugMessageCallback(
		GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam) {

		
		//only show errors and warnings 
		if (type == GL_DEBUG_TYPE_ERROR || type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR)
		{
			fprintf(stderr, "GL CALLBACK: %s\n type = 0x%x, severity = 0x%x,\n message = %s\n\n",
				(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
				type, severity, message);
		}

	}

	OpenGLGraphicsContext::OpenGLGraphicsContext(GLFWwindow* window)
	{
		m_WindowHandle = window;
	}

	void OpenGLGraphicsContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			printf("Failed to initialize GLAD\n");

		printf("OpenGL Info:\n");
		printf("  Vendor: %s\n", glGetString(GL_VENDOR));
		printf("  Renderer: %s\n", glGetString(GL_RENDERER));
		printf("  Version: %s\n", glGetString(GL_VERSION));
		
		#ifdef _ONYX_DEBUG_

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(DebugMessageCallback, 0);

		#endif
	}

	void OpenGLGraphicsContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

	void OpenGLGraphicsContext::DebugGraphicsError(std::string_view error)
	{
		printf("OpenGL Error: %s\n", error.data());
	}

}

