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
		inline static Application* Get() { return s_Instance; };		
		
		Window& GetOnyxWindow() const { return *m_Window; };
		void Run();
		void OnEvent(Event& e);

	private:
		Window* m_Window = nullptr;
		RendererAPI* m_RendererAPI = nullptr;
		static Application* s_Instance;


	};


}

Onyx::Application* CreateApplication();

#endif // !_ONYX_APPLICATION_H_
