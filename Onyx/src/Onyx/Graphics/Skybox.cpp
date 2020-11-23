#include "onyxpch.h"
#include "Skybox.h"
#include "Texture.h"
#include "Shader.h"

#include <Onyx/Graphics/RenderCommand.h>

#include <glad/glad.h>

namespace Onyx {

	std::vector<glm::vec3> SkyboxVertices = {
		// positions          
		{-1.0f,  1.0f, -1.0f},
		{-1.0f, -1.0f, -1.0f},
		{ 1.0f, -1.0f, -1.0f},
		{ 1.0f, -1.0f, -1.0f},
		{ 1.0f,  1.0f, -1.0f},
		{-1.0f,  1.0f, -1.0f},

		{-1.0f, -1.0f,  1.0f},
		{-1.0f, -1.0f, -1.0f},
		{-1.0f,  1.0f, -1.0f},
		{-1.0f,  1.0f, -1.0f},
		{-1.0f,  1.0f,  1.0f},
		{-1.0f, -1.0f,  1.0f},

		{ 1.0f, -1.0f, -1.0f},
		{ 1.0f, -1.0f,  1.0f},
		{ 1.0f,  1.0f,  1.0f},
		{ 1.0f,  1.0f,  1.0f},
		{ 1.0f,  1.0f, -1.0f},
		{ 1.0f, -1.0f, -1.0f},

		{-1.0f, -1.0f,  1.0f},
		{-1.0f,  1.0f,  1.0f},
		{ 1.0f,  1.0f,  1.0f},
		{ 1.0f,  1.0f,  1.0f},
		{ 1.0f, -1.0f,  1.0f},
		{-1.0f, -1.0f,  1.0f},

		{-1.0f,  1.0f, -1.0f},
		{ 1.0f,  1.0f, -1.0f},
		{ 1.0f,  1.0f,  1.0f},
		{ 1.0f,  1.0f,  1.0f},
		{-1.0f,  1.0f,  1.0f},
		{-1.0f,  1.0f, -1.0f},

		{-1.0f, -1.0f, -1.0f},
		{-1.0f, -1.0f,  1.0f},
		{ 1.0f, -1.0f, -1.0f},
		{ 1.0f, -1.0f, -1.0f},
		{-1.0f, -1.0f,  1.0f},
		{ 1.0f, -1.0f,  1.0f}
	};

	Skybox::Skybox(std::vector<std::string> paths)
	{
		m_SkyboxTexture = Cubemap::Create(paths);

		m_SkyboxVAO = VertexArray::Create();

		m_SkyboxVBO = VertexBuffer::Create(reinterpret_cast<float*>(SkyboxVertices.data()), SkyboxVertices.size() * sizeof(glm::vec3));
		
		m_SkyboxVAO->AddVertexBuffer(m_SkyboxVBO);

		m_SkyboxVBO->Bind();
		m_SkyboxVAO->Bind();

		//setup layout
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		

	}

	void Skybox::Draw()
	{
		m_SkyboxVBO->Bind();
		m_SkyboxVAO->Bind();
		m_SkyboxTexture->Bind();


		RenderCommand::DrawArrays(m_SkyboxVAO, 36);

	}



}