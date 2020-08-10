#include "onyxpch.h"
#include "OpenGLRenderer2D.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include <Onyx/Graphics/RenderCommand.h>

#include <array>


namespace Onyx {

	struct Vertex2D {

#define Vertex2D_NO_TEXTURE 0.0f

		glm::vec3 Position;
		glm::vec4 Color;
		float TexID; // 0 = no texture bound to quad
		glm::vec2 TexCoord;



	};


	struct Renderer2DData {
		
		static const uint32_t MaxTextureSlots = 32;


		Texture2D* WhiteTexture;
		std::array<Texture2D*, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1; // 0 = white texture


	};

	static Renderer2DData s_Data;

	void OpenGLRenderer2D::initImplementation()
	{
		const uint32_t MAX_QUADS = 250000;
		const uint32_t VB_SIZE = MAX_QUADS * sizeof(Vertex2D) * 4;
		const uint32_t IB_COUNT = MAX_QUADS * 6;

		m_QuadVertexArray = (OpenGLVertexArray*)VertexArray::create();

		m_QuadVertexBuffer = (OpenGLVertexBuffer*)VertexBuffer::create(VB_SIZE);

		m_QuadVertexArray->addVertexBuffer(m_QuadVertexBuffer);
		
		m_QuadVertexBuffer->bind();

		//TODO: buffer layout needs work
		m_QuadVertexArray->bind();

		//index, size of each vertex, type, normalized?, byte size of each vertex packet, offset into packet for data
		
		//position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)offsetof(Vertex2D, Vertex2D::Position));


		//color
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)offsetof(Vertex2D, Vertex2D::Color));

		//texture_id 0 = no texture
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)offsetof(Vertex2D, Vertex2D::TexID));


		//tex-coord
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)offsetof(Vertex2D, Vertex2D::TexCoord));
		


		uint32_t* indices = new uint32_t[IB_COUNT];
		int offset = 0;

		for (int i = 0; i < IB_COUNT; i+=6) {
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;
		
			offset += 4;
		}

		m_QuadIndexBuffer = (OpenGLIndexBuffer*)IndexBuffer::create(indices, IB_COUNT);
		m_QuadVertexArray->setIndexBuffer(m_QuadIndexBuffer);

		delete[] indices;

		m_QuadVertexBufferData = new Vertex2D[MAX_QUADS * 4];
		m_QuadVertexBufferWritePtr = m_QuadVertexBufferData;


		//create textures and sampler for the 32 texture slots

		s_Data.WhiteTexture = Texture2D::create(1, 1);
		uint32_t pureWhiteTexture = 0xffffffff;
		s_Data.WhiteTexture->setData(&pureWhiteTexture, sizeof(uint32_t));

		int32_t samplers[s_Data.MaxTextureSlots];
		for (uint32_t i = 0; i < s_Data.MaxTextureSlots; i++)
			samplers[i] = i;

		//set 0th to white texture
		s_Data.TextureSlots[0] = s_Data.WhiteTexture;
		
		//set samplers in shader
		m_QuadShader = (OpenGLShader*)Shader::create("res/shaders/Texture.glsl");
		m_QuadShader->bind();
		m_QuadShader->uploadIntArray("u_Textures", samplers, s_Data.MaxTextureSlots);


	}

	void OpenGLRenderer2D::destroyImplementation()
	{
		delete[] m_QuadVertexBufferData;
	}

	void OpenGLRenderer2D::beginSceneImplementation(const OrthographicCamera& camera)
	{
		m_QuadVertexBufferWritePtr = m_QuadVertexBufferData;
		m_IndexCount = 0;

		m_QuadShader->bind();		
		((OpenGLShader*)m_QuadShader)->uploadUniformMat4("u_ViewProjection", camera.getViewProjectionMatrix());

		s_Data.TextureSlotIndex = 1;
	}

	void OpenGLRenderer2D::endSceneImplementation()
	{
		unsigned long long vertexBufferSize = (unsigned char*)m_QuadVertexBufferWritePtr - (unsigned char*)m_QuadVertexBufferData;

		if (vertexBufferSize != 0) {
			//set vertex buffer to draw
			m_QuadVertexBuffer->setData((void*)m_QuadVertexBufferData, vertexBufferSize);
		}

	}

	void OpenGLRenderer2D::drawQuadImplementation(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		drawQuad(glm::vec3(position, 0.0f), size, color);
	}

	void OpenGLRenderer2D::drawQuadImplementation(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{

		m_QuadVertexBufferWritePtr->Position = position;
		m_QuadVertexBufferWritePtr->Color = color;
		m_QuadVertexBufferWritePtr->TexID = Vertex2D_NO_TEXTURE;
		m_QuadVertexBufferWritePtr->TexCoord = glm::vec2(0.0f, 0.0f);
		m_QuadVertexBufferWritePtr++;

		m_QuadVertexBufferWritePtr->Position = position + glm::vec3(size.x, 0.0f, 0.0f);
		m_QuadVertexBufferWritePtr->Color = color;
		m_QuadVertexBufferWritePtr->TexID = Vertex2D_NO_TEXTURE;
		m_QuadVertexBufferWritePtr->TexCoord = glm::vec2(1.0f, 0.0f);
		m_QuadVertexBufferWritePtr++;

		m_QuadVertexBufferWritePtr->Position = position + glm::vec3(size.x, size.y, 0.0f);
		m_QuadVertexBufferWritePtr->Color = color;
		m_QuadVertexBufferWritePtr->TexID = Vertex2D_NO_TEXTURE;
		m_QuadVertexBufferWritePtr->TexCoord = glm::vec2(1.0f, 1.0f);
		m_QuadVertexBufferWritePtr++;

		m_QuadVertexBufferWritePtr->Position = position + glm::vec3(0.0f, size.y, 0.0f);
		m_QuadVertexBufferWritePtr->Color = color;
		m_QuadVertexBufferWritePtr->TexID = Vertex2D_NO_TEXTURE;
		m_QuadVertexBufferWritePtr->TexCoord = glm::vec2(0.0f, 1.0f);
		m_QuadVertexBufferWritePtr++;

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, position.z });
		((OpenGLShader*)m_QuadShader)->uploadUniformMat4("u_Transform", transform);
		m_IndexCount += 6;

	}

	void OpenGLRenderer2D::drawQuadImplementation(const glm::vec3& position, const glm::vec2& size, Texture2D* texture)
	{

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
		{
			if (*s_Data.TextureSlots[i] == *texture)
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			//if (s_Data.TextureSlotIndex >= Renderer2DData::MaxTextureSlots)
				//FlushAndReset();

			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}


		m_QuadVertexBufferWritePtr->Position = position;
		m_QuadVertexBufferWritePtr->Color = glm::vec4(1,1,1,1);
		m_QuadVertexBufferWritePtr->TexID = textureIndex;
		m_QuadVertexBufferWritePtr->TexCoord = glm::vec2(0.0f, 0.0f);
		m_QuadVertexBufferWritePtr++;

		m_QuadVertexBufferWritePtr->Position = position + glm::vec3(size.x, 0.0f, 0.0f);
		m_QuadVertexBufferWritePtr->Color = glm::vec4(1, 1, 1, 1);
		m_QuadVertexBufferWritePtr->TexID = textureIndex;
		m_QuadVertexBufferWritePtr->TexCoord = glm::vec2(1.0f, 0.0f);
		m_QuadVertexBufferWritePtr++;

		m_QuadVertexBufferWritePtr->Position = position + glm::vec3(size.x, size.y, 0.0f);
		m_QuadVertexBufferWritePtr->Color = glm::vec4(1,1,1,1);
		m_QuadVertexBufferWritePtr->TexID = textureIndex;
		m_QuadVertexBufferWritePtr->TexCoord = glm::vec2(1.0f, 1.0f);
		m_QuadVertexBufferWritePtr++;

		m_QuadVertexBufferWritePtr->Position = position + glm::vec3(0.0f, size.y, 0.0f);
		m_QuadVertexBufferWritePtr->Color = glm::vec4(1, 1, 1, 1);
		m_QuadVertexBufferWritePtr->TexID = textureIndex;
		m_QuadVertexBufferWritePtr->TexCoord = glm::vec2(0.0f, 1.0f);
		m_QuadVertexBufferWritePtr++;

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, position.z });
		((OpenGLShader*)m_QuadShader)->uploadUniformMat4("u_Transform", transform);
		m_IndexCount += 6;

	}

	void OpenGLRenderer2D::flushImplementation()
	{
		if (m_IndexCount == 0)
			return;

		//bind textures
		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
			s_Data.TextureSlots[i]->bind(i);
		
		RenderCommand::DrawIndexed(m_QuadVertexArray, m_IndexCount);
		glBindTextureUnit(0, 0);
	}

}