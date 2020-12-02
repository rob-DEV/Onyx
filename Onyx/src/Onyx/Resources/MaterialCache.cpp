#include "onyxpch.h"
#include "MaterialCache.h"

namespace Onyx {

	bool MaterialCache::Exists(std::string_view name) const
	{
		return m_MaterialCache.find(name.data()) != m_MaterialCache.end();
	}

	Material* MaterialCache::GetMaterial(std::string_view name) const
	{
		if (!Exists(name)) {
			ONYX_ERROR("MaterialCache ERROR: Requested Material does not exist");
		}

		return m_MaterialCache.at(name.data());
	}

	Material* MaterialCache::CacheMaterial(std::string_view name, Material material, bool overrideExisting)
	{
		if (!Exists(name)) {
			m_MaterialCache[name.data()] = new Material(material);
		}
		else if(overrideExisting) {
			ONYX_LOG("WARN: Adding an already added material");
			delete m_MaterialCache.at(name.data());
			m_MaterialCache[name.data()] = new Material(material);
		}

		return m_MaterialCache.at(name.data());
	}

}
