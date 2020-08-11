#ifndef _ONYX_GRAPHICS_SHADER_H_
#define _ONYX_GRAPHICS_SHADER_H_

#include <Onyx/core/Core.h>

#include <unordered_map>

namespace Onyx {

	class ONYX_API Shader
	{
	public:

		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const std::string& GetName() const = 0;

		static Shader* Create(const std::string& filepath);
		static Shader* Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);

	};

	class ONYX_API ShaderLibrary {
	public:
		void Add(const std::string& name, Shader* shader);
		void Add(Shader* shader);
		Shader* Load(const std::string& filepath);
		Shader* Load(const std::string& name, const std::string& filepath);

		Shader* Get(const std::string& name);

		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Shader*> m_Shaders;
	};

}


#endif // !_ONYX_GRAPHICS_SHADER_H_