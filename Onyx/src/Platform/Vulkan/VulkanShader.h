#ifndef _ONYX_PLATFORM_VULKAN_SHADER_H_
#define _ONYX_PLATFORM_VULKAN_SHADER_H_

#include <Onyx/Graphics/Shader.h>

namespace Onyx {

	class VulkanShader : Shader {
	public:
		VulkanShader(const std::string& filepath);
		VulkanShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		~VulkanShader();


		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual const std::string& getName() const = 0;


	};


}



#endif // !_ONYX_PLATFORM_VULKAN_SHADER_H_
