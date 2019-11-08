#ifndef _ONYX_APPLICATION_H_
#define _ONYX_APPLICATION_H_

#include "Core.h"
#include "Window.h"

#include <Onyx/graphics/RendererAPI.h>
#include <Onyx/graphics/Renderer2D.h>

namespace Onyx {
	class ONYX_API Application {
	public:

		Application();
		virtual ~Application();
		inline static Application* get() { return s_Instance; };
		
		Window& getOnyxWindow() const { return *m_Window; };
		void run();

	protected:
	private:
		Window* m_Window;
		
		RendererAPI* m_RendererAPI;
		
		static Application* s_Instance;
	};


}

Onyx::Application* CreateApplication();


#endif // !_ONYX_APPLICATION_H_
