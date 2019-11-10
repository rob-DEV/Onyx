#include "onyxpch.h"
#include "Shader.h"

#include "RendererAPI.h"
#include <Platform/OpenGL/OpenGLShader.h>

namespace Onyx {

	Shader* Shader::create(const std::string& filepath)
	{
		if (RendererAPI::getAPI() == RendererAPI::API::OpenGL)
			return new OpenGLShader(filepath);

		printf("Shader is nullptr!\n");
		return nullptr;
	}


	Shader* Shader::create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		if (RendererAPI::getAPI() == RendererAPI::API::OpenGL)
			return new OpenGLShader(name, vertexSrc, fragmentSrc);
		
		return nullptr;

	}

	void ShaderLibrary::add(const std::string& name, Shader* shader)
	{
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::add(Shader* shader)
	{
		const std::string& name = shader->getName();
		m_Shaders[name] = shader;
	}

	Onyx::Shader* ShaderLibrary::load(const std::string& filepath)
	{
		Shader* shader = Shader::create(filepath);
		add(shader);
		return shader;
	}

	Onyx::Shader* ShaderLibrary::load(const std::string& name, const std::string& filepath)
	{
		Shader* shader = Shader::create(filepath);
		add(name, shader);
		return shader;
	}

	Onyx::Shader* ShaderLibrary::get(const std::string& name)
	{
		if (!exists(name))
			printf("Can't find shader!\n");
		return m_Shaders[name];
	}

	bool ShaderLibrary::exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}