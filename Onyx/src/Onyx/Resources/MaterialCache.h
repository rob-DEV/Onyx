#ifndef _ONYX_RESOURCES_MATERIAL_CACHE_H_
#define _ONYX_RESOURCES_MATERIAL_CACHE_H_

#include <unordered_map>
#include <Onyx/Graphics/Material.h>

namespace Onyx {

	class MaterialCache
	{
		MaterialCache() = default;
		~MaterialCache() = default;
	public:

		static auto& Get() {
			static MaterialCache instance;
			return instance;
		}

		bool Exists(std::string_view name) const;

		Material* GetMaterial(std::string_view name) const;
		Material* CacheMaterial(std::string_view name, Material material, bool overrideExisting = false);

		uint32_t GetMaterialCount() const { return m_MaterialCache.size(); }


	private:
		std::unordered_map<std::string, Material*> m_MaterialCache;
	};

}
#endif // !_ONYX_RESOURCES_MATERIAL_CACHE_H_
