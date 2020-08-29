#include "onyxpch.h"
#include "OpenGLRendererAPI.h"


#include <Onyx/Core/Application.h>
#include <glad/glad.h>

namespace Onyx {

	void OpenGLRendererAPI::Init()
	{
		
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthFunc(GL_LEQUAL);

	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawArrays(VertexArray* vertexArray, uint32_t count)
	{
		glDrawArrays(GL_TRIANGLES, 0, count);
	}

	void OpenGLRendererAPI::DrawIndexed(VertexArray* vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::DrawIndexed(VertexArray* vertexArray, uint32_t indexCount)
	{
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);

	}

	////EXPERIMENTAL
	//TODO: Abstract to framebuffer class
	RenderedPixelData OpenGLRendererAPI::GetRenderedFrameBuffer()
	{
		constexpr uint32_t width = 960;
		constexpr uint32_t height = 540;
		constexpr uint32_t frameBufferSize = 3 * width * height;

		RenderedPixelData renderedFrame(NULL, 0);
		char* pixelData = new char[frameBufferSize];
		glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixelData);
		renderedFrame.Data = pixelData;
		renderedFrame.Size = frameBufferSize;

		return renderedFrame;

	}

}