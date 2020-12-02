#include "onyxpch.h"
#include "Shader.h"

#include "RendererAPI.h"
#include <Platform/OpenGL/OpenGLShader.h>

namespace Onyx {

	std::unordered_map<std::string, Shader*> ShaderCache::m_ShaderCache = std::unordered_map<std::string, Shader*>();

	Shader* Shader::Create(std::string_view filepath)
	{
		if (RendererAPI::GetAPI() == RendererAPI::API::OpenGL)
			return new OpenGLShader(filepath);

		printf("Shader is nullptr!\n");
		return nullptr;
	}


	Shader* Shader::Create(std::string_view name, std::string_view vertexSrc, std::string_view fragmentSrc)
	{
		if (RendererAPI::GetAPI() == RendererAPI::API::OpenGL)
			return new OpenGLShader(name, vertexSrc, fragmentSrc);
		
		return nullptr;

	}

	void ShaderCache::Add(std::string_view name, Shader* shader)
	{
		m_ShaderCache[name.data()] = shader;
	}

	Shader* ShaderCache::Load(std::string_view name, std::string_view filepath)
	{
		Shader* shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Shader* ShaderCache::Get(std::string_view name)
	{
		if (!Exists(name))
			printf("Can't find shader!\n");
		return m_ShaderCache[name.data()];
	}

	bool ShaderCache::Exists(std::string_view name)
	{
		return m_ShaderCache.find(name.data()) != m_ShaderCache.end();
	}

}