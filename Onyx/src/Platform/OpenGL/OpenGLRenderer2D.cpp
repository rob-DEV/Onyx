#include "onyxpch.h"
#include "OpenGLRenderer2D.h"
#include <Onyx/Graphics/RenderCommand.h>

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

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

		glm::vec4 QuadVertexPositions[4];
		

	};

	static Renderer2DData s_Data;

	void OpenGLRenderer2D::InitImplementation()
	{
		const uint32_t MAX_QUADS = 250000;
		const uint32_t VB_SIZE = MAX_QUADS * sizeof(Vertex2D) * 4;
		const uint32_t IB_COUNT = MAX_QUADS * 6;

		m_QuadVertexArray = (OpenGLVertexArray*)VertexArray::Create();

		m_QuadVertexBuffer = (OpenGLVertexBuffer*)VertexBuffer::Create(VB_SIZE);

		m_QuadVertexArray->AddVertexBuffer(m_QuadVertexBuffer);
		
		m_QuadVertexBuffer->Bind();

		//TODO: buffer layout needs work
		m_QuadVertexArray->Bind();

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

		m_QuadIndexBuffer = (OpenGLIndexBuffer*)IndexBuffer::Create(indices, IB_COUNT);
		m_QuadVertexArray->SetIndexBuffer(m_QuadIndexBuffer);

		delete[] indices;

		m_QuadVertexBufferData = new Vertex2D[MAX_QUADS * 4];
		m_QuadVertexBufferWritePtr = m_QuadVertexBufferData;


		//create textures and sampler for the 32 texture slots

		s_Data.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t pureWhiteTexture = 0xffffffff;
		s_Data.WhiteTexture->SetData(&pureWhiteTexture, sizeof(uint32_t));

		int32_t samplers[s_Data.MaxTextureSlots];
		for (uint32_t i = 0; i < s_Data.MaxTextureSlots; i++)
			samplers[i] = i;

		//set 0th to white texture
		s_Data.TextureSlots[0] = s_Data.WhiteTexture;
		
		//set samplers in shader
		m_QuadShader = (OpenGLShader*)Shader::Create("res/shaders/Texture.glsl");
		m_QuadShader->Bind();
		m_QuadShader->UploadIntArray("u_Textures", samplers, s_Data.MaxTextureSlots);

		s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };


	}

	void OpenGLRenderer2D::DestroyImplementation()
	{
		delete[] m_QuadVertexBufferData;
	}

	void OpenGLRenderer2D::BeginSceneImplementation(const OrthographicCamera& camera)
	{
		m_QuadVertexBufferWritePtr = m_QuadVertexBufferData;
		m_IndexCount = 0;

		m_QuadShader->Bind();		
		((OpenGLShader*)m_QuadShader)->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		s_Data.TextureSlotIndex = 1;
	}

	void OpenGLRenderer2D::EndSceneImplementation()
	{
		unsigned long long vertexBufferSize = (unsigned char*)m_QuadVertexBufferWritePtr - (unsigned char*)m_QuadVertexBufferData;

		if (vertexBufferSize != 0) {
			//set vertex buffer to draw
			m_QuadVertexBuffer->SetData((void*)m_QuadVertexBufferData, vertexBufferSize);
		}

	}

	void OpenGLRenderer2D::FlushImplementation()
	{
		if (m_IndexCount == 0)
			return;

		//bind textures
		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
			s_Data.TextureSlots[i]->Bind(i);

		RenderCommand::DrawIndexed(m_QuadVertexArray, m_IndexCount);
		glBindTextureUnit(0, 0);
	}

	void OpenGLRenderer2D::DrawQuadImplementation(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuadImplementation(transform, color);

	}

	void OpenGLRenderer2D::DrawQuadImplementation(const glm::vec3& position, const glm::vec2& size, Texture2D* texture)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuadImplementation(transform, texture);

	}


	void OpenGLRenderer2D::DrawQuadImplementation(const glm::mat4& transform, const glm::vec4& color)
	{
		constexpr size_t quadVertexCount = 4;
		const float textureIndex = 0.0f; // White Texture
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		const float tilingFactor = 1.0f;



		for (size_t i = 0; i < quadVertexCount; i++)
		{
			m_QuadVertexBufferWritePtr->Position = transform * s_Data.QuadVertexPositions[i];
			m_QuadVertexBufferWritePtr->Color = color;
			m_QuadVertexBufferWritePtr->TexID = Vertex2D_NO_TEXTURE;
			m_QuadVertexBufferWritePtr->TexCoord = textureCoords[i];
			m_QuadVertexBufferWritePtr++;
		}

		m_IndexCount += 6;

	}

	void OpenGLRenderer2D::DrawQuadImplementation(const glm::mat4& transform, Texture2D* texture)
	{
		constexpr size_t quadVertexCount = 4;
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

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

			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}

		for (size_t i = 0; i < quadVertexCount; i++)
		{
			m_QuadVertexBufferWritePtr->Position = transform * s_Data.QuadVertexPositions[i];
			m_QuadVertexBufferWritePtr->Color = glm::vec4(1, 1, 1, 1);
			m_QuadVertexBufferWritePtr->TexID = textureIndex;
			m_QuadVertexBufferWritePtr->TexCoord = textureCoords[i];
			m_QuadVertexBufferWritePtr++;
		}


		m_IndexCount += 6;
	}

	void OpenGLRenderer2D::DrawRotatedQuadImplementation(const glm::vec3& position, float angle, const glm::vec3& ax, const glm::vec2& size, const glm::vec4& color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(angle), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuadImplementation(transform, color);

	}

	void OpenGLRenderer2D::DrawRotatedQuadImplementation(const glm::vec3& position, float angle, const glm::vec3& ax, const glm::vec2& size, Texture2D* texture)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(angle), ax)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuadImplementation(transform, texture);
	
	}

}