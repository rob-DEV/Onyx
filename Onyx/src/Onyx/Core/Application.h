#ifndef _ONYX_APPLICATION_H_
#define _ONYX_APPLICATION_H_

#include <Onyx/Core/Window.h>
#include <Onyx/Core/Layer.h>

#include <Onyx/Graphics/RendererAPI.h>
#include <Onyx/Graphics/Renderer2D.h>

#include "ApplicationContext.h"

namespace Onyx {

	class ONYX_API Application {
	public:

		Application();

		virtual ~Application();
		inline static Application* Get() { return s_Instance; };		
		
		Window& GetOnyxWindow() const { return *m_Window; };
		void Run();
		void SetWindowTitle(const char* name) { m_Window->SetTitle(name); }

		//TODO: REFACTOR ENTIRE APPLICATION CLASS
		static void SetContext(ApplicationContext context) { s_ApplicationContext = context; }
		static ApplicationContext GetContext() { return s_ApplicationContext; }

	private:
		Window* m_Window = nullptr;
		static Application* s_Instance;
		float m_LastTime;
		static ApplicationContext s_ApplicationContext;
	protected:
		//TODO : redo
		std::vector<Layer*> m_LayerStack;


	};


}

Onyx::Application* CreateApplication();

#endif // !_ONYX_APPLICATION_H_
