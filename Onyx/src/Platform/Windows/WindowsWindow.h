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

		void Init();
		void OnUpdate();

		inline uint32_t GetWidth() { return m_Data.Width; };
		inline uint32_t GetHeight() { return m_Data.Height; };
		inline std::string_view GetTitle() { return m_Data.Title; };
		inline double GetScroll() { return  m_Data.ScrollY; }

		virtual void SetTitle(const char* title);
		virtual bool IsClosed();
		virtual bool IsHidden();
		inline void* GetNativeWindow() { return m_Window; };
		

	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;
		
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			double ScrollX, ScrollY;
			bool Hidden;

		};

		WindowData m_Data;


	};

}


#endif // !_ONYX_PLATFORM_WINDOWS_WINDOW_H_
