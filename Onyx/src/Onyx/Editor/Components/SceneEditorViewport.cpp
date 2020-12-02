#include "onyxpch.h"
#include "SceneEditorViewport.h"
#include <glad/glad.h>
#include <Onyx/Core/Input.h>

#include <glm/vec2.hpp>

namespace Onyx {

	SceneEditorViewport::SceneEditorViewport()
	{
		glGenBuffers(2, pboIds);
		glBindBuffer(GL_PIXEL_PACK_BUFFER, pboIds[0]);
		glBufferData(GL_PIXEL_PACK_BUFFER, 1280 * 720 * 3, 0, GL_STREAM_READ);
		glBindBuffer(GL_PIXEL_PACK_BUFFER, pboIds[1]);
		glBufferData(GL_PIXEL_PACK_BUFFER, 1280 * 720 * 3, 0, GL_STREAM_READ);

		glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
	}

	SceneEditorViewport::~SceneEditorViewport()
	{
		glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
		glDeleteBuffers(2, pboIds);
	}

	void SceneEditorViewport::RenderFrameToBuffer(unsigned int* buffer)
	{
		index = (index + 1) % 2;
		nextIndex = (index + 1) % 2;
		// 
		glReadBuffer(GL_FRONT);
		glBindBuffer(GL_PIXEL_PACK_BUFFER, pboIds[index]);
		glReadPixels(0, 0, 1280, 720, GL_RGB, GL_UNSIGNED_BYTE, 0);

		// map the PBO to process its data by CPU
		glBindBuffer(GL_PIXEL_PACK_BUFFER, pboIds[nextIndex]);
		GLubyte* ptr = (GLubyte*)glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);

		uint64_t pos = 0;
		for (uint64_t i = 0; i < 1280 * 720; ++i)
		{
			buffer[i] = (255 << 24) + (ptr[pos] << 16) + (ptr[pos + 1] << 8) + ptr[pos + 2];
			pos = 3 * i;
		}
		
		if (Input::IsMouseButtonPressed(ONYX_MOUSE_BUTTON_1)) {
			glm::vec2 mousePos = Input::GetMousePosition();
			uint32_t x = (uint32_t)mousePos.x;
			uint32_t y = (uint32_t)mousePos.y;
			uint32_t a = 0x00FFFFFF;
			if (ptr) {
				uint32_t* p = (uint32_t*)ptr;
				if (x < 1280 && y < 720) {
					a = (uint32_t)(p[x + (1280 * y)]);
				}
			}

			printf("Selected Entity at pos %d,%d - 0x%08x\n", x, y, a);
		}

		glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
	}

}