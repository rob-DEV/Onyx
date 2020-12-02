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

		virtual void SetInt(std::string_view name, int value) = 0;
		virtual void SetIntArray(std::string_view name, int* values, uint32_t count) = 0;
		virtual void SetFloat(std::string_view name, float value) = 0;
		virtual void SetFloat2(std::string_view name, const glm::vec2& value) = 0;
		virtual void SetFloat3(std::string_view name, const glm::vec3& value) = 0;
		virtual void SetFloat4(std::string_view name, const glm::vec4& value) = 0;

		virtual void SetMat3(std::string_view name, const glm::mat3& value) = 0;
		virtual void SetMat4(std::string_view name, const glm::mat4& value) = 0;

		virtual std::string_view GetName() const = 0;

		static Shader* Create(std::string_view filepath);
		static Shader* Create(std::string_view name, std::string_view vertexSrc, std::string_view fragmentSrc);

	};

	class ONYX_API ShaderCache {
	public:
		static void Add(std::string_view name, Shader* shader);
		static bool Exists(std::string_view name);

		static Shader* Load(std::string_view name, std::string_view filepath);
		static Shader* Get(std::string_view name);
	private:
		static std::unordered_map<std::string, Shader*> m_ShaderCache;
	};

}


#endif // !_ONYX_GRAPHICS_SHADER_H_