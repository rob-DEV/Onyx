#include "onyxpch.h"
#include "MaterialCache.h"

namespace Onyx {

	bool MaterialCache::Exists(const std::string& name) const
	{
		return m_MaterialCache.find(name) != m_MaterialCache.end();
	}

	Material* MaterialCache::GetMaterial(const std::string& name) const
	{
		if (!Exists(name)) {
			ONYX_ERROR("MaterialCache ERROR: Requested Material does not exist");
		}

		return m_MaterialCache.at(name);
	}

	Material* MaterialCache::CacheMaterial(const std::string& name, Material material, bool overrideExisting)
	{
		if (!Exists(name)) {
			m_MaterialCache[name] = new Material(material);
		}
		else if(overrideExisting) {
			ONYX_LOG("WARN: Adding an already added material");
			delete m_MaterialCache.at(name);
			m_MaterialCache[name] = new Material(material);
		}

		return m_MaterialCache.at(name);
	}

}
