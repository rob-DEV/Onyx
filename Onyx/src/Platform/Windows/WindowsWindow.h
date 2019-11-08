#ifndef _ONYX_PLATFORM_WINDOWS_WINDOW_H_
#define _ONYX_PLATFORM_WINDOWS_WINDOW_H_

#include <Onyx/core/Window.h>
#include <Onyx/graphics/GraphicsContext.h>


struct GLFWwindow;

namespace Onyx { 

	class ONYX_API WindowsWindow : public Window {

	public:

		WindowsWindow();
		WindowsWindow(const WindowProperties& properties);
		~WindowsWindow();

		void init();
		void onUpdate();

		inline uint32_t getWidth() { return m_WindowProperties.Width; };
		inline uint32_t getHeight() { return m_WindowProperties.Height; };
		inline const std::string& getTitle() { return m_WindowProperties.Title; };

		virtual bool isClosed();
		inline void* getNativeWindow() { return m_Window; };
		

	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		WindowProperties m_WindowProperties;

	};

}


#endif // !_ONYX_PLATFORM_WINDOWS_WINDOW_H_
