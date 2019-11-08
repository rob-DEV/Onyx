#ifndef _ONYX_GRAPHICS_SHADER_H_
#define _ONYX_GRAPHICS_SHADER_H_

#include <Onyx/core/Core.h>

#include <unordered_map>

namespace Onyx {

	class ONYX_API Shader
	{
	public:

		virtual ~Shader() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual const std::string& getName() const = 0;

		static Shader* create(const std::string& filepath);
		static Shader* create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);

	public:

	private:

	};

	class ONYX_API ShaderLibrary {
	public:
		void add(const std::string& name, Shader* shader);
		void add(Shader* shader);
		Shader* load(const std::string& filepath);
		Shader* load(const std::string& name, const std::string& filepath);

		Shader* get(const std::string& name);

		bool exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Shader*> m_Shaders;
	};

}


#endif // !_ONYX_GRAPHICS_SHADER_H_