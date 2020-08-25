#include "onyxpch.h"
#include "Registry.h"

#include <entt/entt.hpp>

namespace Onyx {

	Registry::Registry()
	{
		m_Registry = new entt::registry();
	}

	uint32_t Registry::Create()
	{
		return (uint32_t)((entt::registry*)m_Registry)->create();
	}

}