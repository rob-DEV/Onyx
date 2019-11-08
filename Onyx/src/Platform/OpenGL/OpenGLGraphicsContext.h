#ifndef _ONYX_PLATFORM_OPENGL_GRAPHICS_CONTEXT_H_
#define _ONYX_PLATFORM_OPENGL_GRAPHICS_CONTEXT_H_

#include <Onyx/graphics/GraphicsContext.h>

struct GLFWwindow;

namespace Onyx {

	class OpenGLGraphicsContext : public GraphicsContext {

	public:
		
		OpenGLGraphicsContext(GLFWwindow* window);
		void init();
		void swapBuffers();

	private:

		GLFWwindow* m_WindowHandle;

	};


}


#endif // _ONYX_GRAPHICS_CONTEXT_H_
