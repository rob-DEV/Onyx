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

		bool Exists(const std::string& path) const;

		Texture* GetTexture(const std::string& path) const;
		Texture* CacheTexture(const std::string& path, bool overrideExisting = false);
		Texture* CacheTexture(const std::string& path, uint32_t width, uint32_t height, bool overrideExisting = false);

		uint32_t GetTextureCount() const { return m_TextureCache.size(); }


	private:
		std::unordered_map<std::string, Texture*> m_TextureCache;
	};

}
#endif // !_ONYX_RESOURCES_TEXTURE_CACHE_H_