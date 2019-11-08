#ifndef _ONYX_WINDOW_H_
#define  _ONYX_WINDOW_H_

#include "Core.h"

namespace Onyx {

	struct ONYX_API WindowProperties {

		std::string Title;
		uint32_t Width, Height;

		WindowProperties(const std::string& title = "Onyx Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{

		}

	};

	class ONYX_API Window {

	public:

		virtual ~Window() = default;

		virtual void init() = 0;

		virtual void onUpdate() = 0;

		virtual uint32_t getWidth() = 0;
		virtual uint32_t getHeight() = 0;
		virtual const std::string& getTitle() = 0;
		       
		virtual bool isClosed() = 0;
		virtual void* getNativeWindow() = 0;
	};

}
#endif // _ONYX_WINDOW_H_
