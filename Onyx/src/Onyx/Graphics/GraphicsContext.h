#ifndef _ONYX_GRAPHICS_CONTEXT_H_
#define _ONYX_GRAPHICS_CONTEXT_H_

#include <Onyx/core/Core.h>

namespace Onyx {

	class ONYX_API GraphicsContext {
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
		//virtual void DebugGraphicsError(const std::string& error) = 0;
		virtual ~GraphicsContext() = default;
	};

}

#endif // !_ONYX_GRAPHICS_CONTEXT_H_
