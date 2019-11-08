#ifndef _ONYX_GRAPHICS_CONTEXT_H_
#define _ONYX_GRAPHICS_CONTEXT_H_

#include <Onyx/core/Core.h>

namespace Onyx {

	class ONYX_API GraphicsContext {
		public:
			virtual void init() = 0;
			virtual void swapBuffers() = 0;
	};


}

#endif // !_ONYX_GRAPHICS_CONTEXT_H_
