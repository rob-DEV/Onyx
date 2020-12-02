#include "onyxpch.h"
#include "OpenGLShader.h"

#include <Onyx/core/FileIO.h>
#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace Onyx {

	static GLenum ShaderTypeFromString(std::string_view type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		printf("Unknown Shader Type!\n");
		return 0;
	}


	OpenGLShader::OpenGLShader(std::string_view filepath)
	{
		std::string source = FileIO::ReadFileString(filepath);
		auto shaderSources = PreProcess(source);
		Compile(shaderSources);

		// Extract name from filepath
		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind('.');
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filepath.substr(lastSlash, count);


	}

	OpenGLShader::OpenGLShader(std::string_view name, std::string_view vertexSrc, std::string_view fragmentSrc)
	{

		std::unordered_map<GLenum, std::string> shaderSources;
		shaderSources[GL_VERTEX_SHADER] = vertexSrc;
		shaderSources[GL_FRAGMENT_SHADER] = fragmentSrc;

		Compile(shaderSources);

		m_Name = name;
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(std::string_view name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.data());
		glUniform1i(location, value);
	}

	void OpenGLShader::SetIntArray(std::string_view name, int* values, uint32_t count)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.data());
		glUniform1iv(location, count, values);
	}

	void OpenGLShader::SetFloat(std::string_view name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.data());
		glUniform1f(location, value);
	}

	void OpenGLShader::SetFloat2(std::string_view name, const glm::vec2& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.data());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::SetFloat3(std::string_view name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.data());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::SetFloat4(std::string_view name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.data());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetMat3(std::string_view name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.data());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::SetMat4(std::string_view name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.data());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}


	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(std::string_view source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0); //Start of shader type declaration line
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos); //End of shader type declaration line
			if(eol == std::string::npos) printf("Syntax error\n");
			size_t begin = pos + typeTokenLength + 1; //Start of shader type name (after "#type " keyword)
			std::string_view type = source.substr(begin, eol - begin);
			if(!ShaderTypeFromString(type)) printf("Invalid shader type specified\n");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol); //Start of shader code after shader type declaration line
			if(nextLinePos == std::string::npos) printf("Syntax error\n");
			pos = source.find(typeToken, nextLinePos); //Start of next shader type declaration line

			shaderSources[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		GLuint program = glCreateProgram();
		if(shaderSources.size() > 2)
			printf("We only support 2 shaders for now\n");
		std::array<GLenum, 2> glShaderIDs;
		int glShaderIDIndex = 0;
		for (auto& kv : shaderSources)
		{
			GLenum type = kv.first;
			std::string_view source = kv.second;

			GLuint shader = glCreateShader(type);

			const GLchar* sourceCStr = source.data();
			glShaderSource(shader, 1, &sourceCStr, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);
				printf("%s\n", infoLog.data());
				printf("Compilation failure!\n");
				break;
			}

			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}

		m_RendererID = program;

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);

			for (auto id : glShaderIDs)
				glDeleteShader(id);

			printf("%s\n", infoLog.data());
			printf("Shader link failure!\n");
			return;
		}

		for (auto id : glShaderIDs)
		{
			glDetachShader(program, id);
			glDeleteShader(id);
		}
	}

}