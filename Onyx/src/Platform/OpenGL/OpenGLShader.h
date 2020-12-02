#ifndef _ONYX_PLATFORM_OPENGL_SHADER_H_
#define _ONYX_PLATFORM_OPENGL_SHADER_H_

#include <Onyx/graphics/Shader.h>
#include <glm/glm.hpp>

typedef unsigned int GLenum;

namespace Onyx {

	class OpenGLShader : public Shader {
	public:

		OpenGLShader(std::string_view filepath);
		OpenGLShader(std::string_view name, std::string_view vertexSrc, std::string_view fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual std::string_view GetName() const override { return m_Name; }

		virtual void SetInt(std::string_view name, int value) override;
		virtual void SetIntArray(std::string_view name, int* values, uint32_t count) override;
		virtual void SetFloat(std::string_view name, float value) override;
		virtual void SetFloat2(std::string_view name, const glm::vec2& value) override;
		virtual void SetFloat3(std::string_view name, const glm::vec3& value) override;
		virtual void SetFloat4(std::string_view name, const glm::vec4& value) override;

		void SetMat3(std::string_view name, const glm::mat3& matrix);
		void SetMat4(std::string_view name, const glm::mat4& matrix);

	private:
		std::unordered_map<GLenum, std::string> PreProcess(std::string_view source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

	private:
		uint32_t m_RendererID;
		std::string m_Name;

	};

}

#endif // !_ONYX_PLATFORM_OPENGL_SHADER_H_
