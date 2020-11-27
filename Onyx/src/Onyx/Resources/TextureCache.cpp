#include "onyxpch.h"
#include "TextureCache.h"

#include "Hasher.h"

namespace Onyx {

	
	bool TextureCache::Exists(const std::string& path) const
	{
		return m_TextureCache.find(path) != m_TextureCache.end();
	}

	Texture* TextureCache::GetTexture(const std::string& path) const
	{
		if (!Exists(path)) {
			ONYX_ERROR("MaterialCache ERROR: Requested Material does not exist");
		}

		return m_TextureCache.at(path);
	}

	Texture* TextureCache::CacheTexture(const std::string& path, bool overrideExisting /*= false*/)
	{
		if (!Exists(path)) {
			m_TextureCache[path] = Texture2D::Create(path);
		}
		else if (overrideExisting) {
			ONYX_LOG("WARN: Adding an already added material");
			delete m_TextureCache.at(path);
			m_TextureCache[path] = Texture2D::Create(path);
		}

		return m_TextureCache.at(path);
	}

	Texture* TextureCache::CacheTexture(const std::string& path, uint32_t width, uint32_t height, bool overrideExisting /*= false*/)
	{
		if (!Exists(path)) {
			m_TextureCache[path] = Texture2D::Create(width, height);
		}
		else if (overrideExisting) {
			ONYX_LOG("WARN: Adding an already added material");
			delete m_TextureCache.at(path);
			m_TextureCache[path] = Texture2D::Create(width, height);
		}

		return m_TextureCache.at(path);
	}

}