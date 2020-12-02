#ifndef _ONYX_RESOURCES_TEXTURE_CACHE_H_
#define _ONYX_RESOURCES_TEXTURE_CACHE_H_

#include <unordered_map>
#include <Onyx/Graphics/Texture.h>

namespace Onyx {

	class TextureCache
	{
		TextureCache() = default;
		~TextureCache() = default;
	public:

		static auto& Get() {
			static TextureCache instance;
			return instance;
		}

		bool Exists(std::string_view path) const;

		Texture* GetTexture(std::string_view path) const;
		Texture* CacheTexture(std::string_view path, bool overrideExisting = false);
		Texture* CacheTexture(std::string_view path, uint32_t width, uint32_t height, bool overrideExisting = false);

		uint32_t GetTextureCount() const { return m_TextureCache.size(); }


	private:
		std::unordered_map<std::string, Texture*> m_TextureCache;
	};

}
#endif // !_ONYX_RESOURCES_TEXTURE_CACHE_H_