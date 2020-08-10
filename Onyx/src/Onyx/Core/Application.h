#ifndef _ONYX_APPLICATION_H_
#define _ONYX_APPLICATION_H_

#include <Onyx/Core/Window.h>
#include <Onyx/Core/Window.h>
#include <Onyx/Event/Event.h>

#include <Onyx/Graphics/RendererAPI.h>
#include <Onyx/Graphics/Renderer2D.h>

namespace Onyx {
	class ONYX_API Application {
	public:

		Application();
		virtual ~Application();
		inline static Application* get() { return s_Instance; };		
		
		Window& getOnyxWindow() const { return *m_Window; };
		void run();
		void onEvent(Event& e);

	private:
		Window* m_Window = nullptr;
		RendererAPI* m_RendererAPI = nullptr;
		static Application* s_Instance;


	};


}

Onyx::Application* CreateApplication();

#endif // !_ONYX_APPLICATION_H_
