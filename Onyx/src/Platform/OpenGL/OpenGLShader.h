#ifndef _ONYX_PLATFORM_OPENGL_SHADER_H_
#define _ONYX_PLATFORM_OPENGL_SHADER_H_

#include <Onyx/graphics/Shader.h>
#include <glm/glm.hpp>

typedef unsigned int GLenum;

namespace Onyx {

	class OpenGLShader : public Shader {
	public:

		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void bind() const;
		virtual void unbind() const;

		virtual const std::string& getName() const override { return m_Name; }

		void uploadUniformInt(const std::string& name, int value);

		void uploadUniformFloat(const std::string& name, float value);
		void uploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void uploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void uploadUniformFloat4(const std::string& name, const glm::vec4& value);

		void uploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void uploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		std::unordered_map<GLenum, std::string> preProcess(const std::string& source);
		void compile(const std::unordered_map<GLenum, std::string>& shaderSources);

	private:
		uint32_t m_RendererID;
		std::string m_Name;

	};

}

#endif // !_ONYX_PLATFORM_OPENGL_SHADER_H_
