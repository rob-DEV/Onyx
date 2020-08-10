#ifndef _ONYX_PLATFORM_WINDOWS_WINDOW_H_
#define _ONYX_PLATFORM_WINDOWS_WINDOW_H_

#include <Onyx/Core/Window.h>
#include <Onyx/Graphics/GraphicsContext.h>


struct GLFWwindow;

namespace Onyx { 

	class ONYX_API WindowsWindow : public Window {

	public:

		WindowsWindow();
		WindowsWindow(const WindowProperties& properties);
		~WindowsWindow();

		void init();
		void onUpdate();

		inline uint32_t getWidth() { return m_Data.Width; };
		inline uint32_t getHeight() { return m_Data.Height; };
		inline const std::string& getTitle() { return m_Data.Title; };

		inline void setEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

		virtual bool isClosed();
		inline void* getNativeWindow() { return m_Window; };
		

	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;
		
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;


	};

}


#endif // !_ONYX_PLATFORM_WINDOWS_WINDOW_H_
