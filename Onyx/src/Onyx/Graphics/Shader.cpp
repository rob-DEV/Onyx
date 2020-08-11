#include "onyxpch.h"
#include "Shader.h"

#include "RendererAPI.h"
#include <Platform/OpenGL/OpenGLShader.h>

namespace Onyx {

	Shader* Shader::Create(const std::string& filepath)
	{
		if (RendererAPI::GetAPI() == RendererAPI::API::OpenGL)
			return new OpenGLShader(filepath);

		printf("Shader is nullptr!\n");
		return nullptr;
	}


	Shader* Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		if (RendererAPI::GetAPI() == RendererAPI::API::OpenGL)
			return new OpenGLShader(name, vertexSrc, fragmentSrc);
		
		return nullptr;

	}

	void ShaderLibrary::Add(const std::string& name, Shader* shader)
	{
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(Shader* shader)
	{
		const std::string& name = shader->GetName();
		m_Shaders[name] = shader;
	}

	Onyx::Shader* ShaderLibrary::Load(const std::string& filepath)
	{
		Shader* shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Onyx::Shader* ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		Shader* shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Onyx::Shader* ShaderLibrary::Get(const std::string& name)
	{
		if (!Exists(name))
			printf("Can't find shader!\n");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}