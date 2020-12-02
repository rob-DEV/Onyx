#include "onyxpch.h"
#include "TextureCache.h"

#include "Hasher.h"

namespace Onyx {

	
	bool TextureCache::Exists(std::string_view path) const
	{
		return m_TextureCache.find(path.data()) != m_TextureCache.end();
	}

	Texture* TextureCache::GetTexture(std::string_view path) const
	{
		if (!Exists(path)) {
			ONYX_ERROR("MaterialCache ERROR: Requested Material does not exist");
		}

		return m_TextureCache.at(path.data());
	}

	Texture* TextureCache::CacheTexture(std::string_view path, bool overrideExisting /*= false*/)
	{
		if (!Exists(path)) {
			m_TextureCache[path.data()] = Texture2D::Create(path.data());
		}
		else if (overrideExisting) {
			ONYX_LOG("WARN: Adding an already added material");
			delete m_TextureCache.at(path.data());
			m_TextureCache[path.data()] = Texture2D::Create(path);
		}

		return m_TextureCache.at(path.data());
	}

	Texture* TextureCache::CacheTexture(std::string_view path, uint32_t width, uint32_t height, bool overrideExisting /*= false*/)
	{
		if (!Exists(path)) {
			m_TextureCache[path.data()] = Texture2D::Create(width, height);
		}
		else if (overrideExisting) {
			ONYX_LOG("WARN: Adding an already added material");
			delete m_TextureCache.at(path.data());
			m_TextureCache[path.data()] = Texture2D::Create(width, height);
		}

		return m_TextureCache.at(path.data());
	}

}