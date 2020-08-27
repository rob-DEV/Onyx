#ifndef _ONYX_WINDOW_H_
#define  _ONYX_WINDOW_H_

#include "onyxpch.h"
#include <Onyx/Core/Core.h>

namespace Onyx {

	struct ONYX_API WindowProperties {

		std::string Title;
		uint32_t Width, Height;
		bool Hidden;

		WindowProperties(const std::string& title = "Onyx Engine",
			unsigned int width = 1280,
			unsigned int height = 720,
			bool isHidden = false)
			: Title(title), Width(width), Height(height), Hidden(isHidden)
		{

		}

	};

	class ONYX_API Window {

	public:

		virtual ~Window() = default;

		virtual void Init() = 0;
		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() = 0;
		virtual uint32_t GetHeight() = 0;
		virtual const std::string& GetTitle() = 0;
		virtual double GetScroll() = 0;
		virtual void SetTitle(const char* title) = 0;
		       
		virtual bool IsClosed() = 0;
		virtual bool IsHidden() = 0;
		virtual void* GetNativeWindow() = 0;
	};

}
#endif // _ONYX_WINDOW_H_
