#ifndef _ONYX_GRAPHICS_TEXTURE_H_
#define _ONYX_GRAPHICS_TEXTURE_H_

#include "Onyx/Core/Core.h"

#include <string>

namespace Onyx {

	class ONYX_API Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual void SetData(void* data, uint32_t size) = 0;
		virtual void Bind(uint32_t slot = 0) const = 0;

		virtual bool operator==(const Texture& other) const = 0;
	};


	class ONYX_API Texture2D : public Texture {
	public:
		static Texture2D* Create(uint32_t width, uint32_t height);
		static Texture2D* Create(const std::string& path);
		inline static int count = 0;
	};

	class ONYX_API Cubemap {

	public:
		virtual ~Cubemap() = default;
		virtual void Bind(uint32_t slot = 0) const = 0;

		static Cubemap* Create(const std::vector<std::string>& paths);

		virtual bool operator==(const Texture& other) const = 0;
	};


}

#endif // !_ONYX_GRAPHICS_TEXTURE_H_
