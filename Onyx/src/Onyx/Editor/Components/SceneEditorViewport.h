#ifndef _ONYX_EDITOR_RENDERER_H_
#define _ONYX_EDITOR_RENDERER_H_

#include <Onyx/Core/Input.h>

namespace Onyx {

	class SceneEditorViewport
	{
	public:
		SceneEditorViewport();
		~SceneEditorViewport();

		void RenderFrameToBuffer(unsigned int* buffer);
	private:
		uint32_t index = 0;
		uint32_t nextIndex = 0;
		uint32_t pboIds[2];
	};

}
#endif // !_ONYX_EDITOR_RENDERER_H_