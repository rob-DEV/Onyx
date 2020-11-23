#ifndef _ONYX_GRAPHICS_SHADER_H_
#define _ONYX_GRAPHICS_SHADER_H_

#include <Onyx/core/Core.h>

#include <glm/glm.hpp>

#include <unordered_map>

namespace Onyx {

	class ONYX_API Shader
	{
	public:

		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetInt(const std::string& name, int value) = 0;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) = 0;
		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) = 0;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;

		virtual void SetMat3(const std::string& name, const glm::mat3& value) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

		virtual const std::string& GetName() const = 0;

		static Shader* Create(const std::string& filepath);
		static Shader* Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);

	};

	class ONYX_API ShaderLibrary {
	public:
		static void Add(const std::string& name, Shader* shader);
		static Shader* Load(const std::string& name, const std::string& filepath);

		static Shader* Get(const std::string& name);

		static bool Exists(const std::string& name);
	private:
		static std::unordered_map<std::string, Shader*> m_ShaderCache;
	};

}


#endif // !_ONYX_GRAPHICS_SHADER_H_