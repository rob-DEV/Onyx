#include "onyxpch.h"
#include "SceneEditorViewport.h"
#include <glad/glad.h>
#include <Onyx/Core/Input.h>

#include <glm/vec2.hpp>

namespace Onyx {

#define RESOLUTION 1130 * 636
#define BUFFER_DEMENSIONS RESOLUTION * 3
	SceneEditorViewport::SceneEditorViewport()
	{
// 		glGenBuffers(2, pboIds);
// 		glBindBuffer(GL_PIXEL_PACK_BUFFER, pboIds[0]);
// 		glBufferData(GL_PIXEL_PACK_BUFFER, RESOLUTION * 4, 0, GL_STREAM_READ);
// 		glBindBuffer(GL_PIXEL_PACK_BUFFER, pboIds[1]);
// 		glBufferData(GL_PIXEL_PACK_BUFFER, RESOLUTION * 4, 0, GL_STREAM_READ);
// 
// 		//selection buffer
// 		glGenBuffers(2, selectionPboIds);
// 		glBindBuffer(GL_PIXEL_PACK_BUFFER, selectionPboIds[0]);
// 		glBufferData(GL_PIXEL_PACK_BUFFER, 1 * 1 * 4, 0, GL_STREAM_READ);
// 		glBindBuffer(GL_PIXEL_PACK_BUFFER, selectionPboIds[1]);
// 		glBufferData(GL_PIXEL_PACK_BUFFER, 1 * 1 * 4, 0, GL_STREAM_READ);
// 
// 		glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
	}

	SceneEditorViewport::~SceneEditorViewport()
	{
		glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
		glDeleteBuffers(2, pboIds);
	}

	void SceneEditorViewport::RenderFrameToBuffer(unsigned int* buffer)
 	{
// 		index = (index + 1) % 2;
// 		nextIndex = (index + 1) % 2;
// 		// 
// 		glReadBuffer(GL_COLOR_ATTACHMENT0);
// 		glBindBuffer(GL_PIXEL_PACK_BUFFER, pboIds[index]);
// 		glReadPixels(0, 0, 1130, 636, GL_RGBA, GL_UNSIGNED_BYTE, 0);
// 
// 		// map the PBO to process its data by CPU
// 		glBindBuffer(GL_PIXEL_PACK_BUFFER, pboIds[nextIndex]);
// 		GLubyte* ptr = (GLubyte*)glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);
// 
// 		uint64_t pos = 0;
// 		for (uint64_t i = 0; i < RESOLUTION; ++i)
// 		{
// 			buffer[i] = (255 << 24) + (ptr[pos] << 16) + (ptr[pos + 1] << 8) + ptr[pos + 2];
// 			pos = 4 * i;
// 		}
// 
// 		glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
// 		
// 		if (Input::IsMouseButtonPressed(ONYX_MOUSE_BUTTON_1)) {
// 			glm::vec2 mousePos = Input::GetMousePosition();
// 
// 			//switch to selection buffer
// 			glReadBuffer(GL_COLOR_ATTACHMENT1);
// 			glBindBuffer(GL_PIXEL_PACK_BUFFER, selectionPboIds[index]);
// 
// 			uint32_t x = (uint32_t)mousePos.x;
// 			uint32_t y = (uint32_t)mousePos.y;
// 			glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, 0);
// 
// 			glBindBuffer(GL_PIXEL_PACK_BUFFER, selectionPboIds[nextIndex]);
// 			GLubyte* selectionBufferPtr = (GLubyte*)glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);
// 
// 			if (ptr) {
// 				uint32_t* p = (uint32_t*)selectionBufferPtr;
// 					SelectedPixel = (uint32_t)(p[0]);
// 			}
// 			printf("0x%8x\n", SelectedPixel);
// 
// 			glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
// 		}

		
	}

}