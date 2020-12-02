#ifndef _ONYX_APPLICATION_H_
#define _ONYX_APPLICATION_H_

#include <Onyx/Core/Window.h>
#include <Onyx/Core/Layer.h>

#include <Onyx/Graphics/RendererAPI.h>
#include <Onyx/Graphics/Renderer2D.h>

namespace Onyx {

	enum class ApplicationContext {
		Runtime = 0,
		Editor
	};

	class Application {
	public:
		virtual ~Application() = default;

		inline static Application* Get() { return s_Instance; };
		
		inline ApplicationContext GetContext() { return s_ApplicationContext; };
		Window& GetOnyxWindow() const { return *m_Window; };

	protected:
		inline static Application* s_Instance = nullptr;
		
		Window* m_Window = nullptr;
		ApplicationContext s_ApplicationContext = ApplicationContext::Runtime;
		Timestep m_EditorTimestep = 0;
	};

}

#endif // !_ONYX_APPLICATION_H_
