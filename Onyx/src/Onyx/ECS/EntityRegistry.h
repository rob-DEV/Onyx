#ifndef _ONYX_ECS_ENTITY_REGISTRY_H_
#define _ONYX_ECS_ENTITY_REGISTRY_H_

#include <Onyx/Core/Core.h>

#include "Types.h"
#include "ComponentArray.h"

#include <queue>

#include <cassert>

namespace Onyx {

	class ECSEntityRegistry {
	public:
		ECSEntityRegistry() {
			for (ECSEntity entity = 0; entity < MAX_ENTITIES; ++entity)
			{
				m_AvailableECSEntities.push(entity);
			}
		};
		~ECSEntityRegistry() {}

		ECSEntity Create() {
			assert(m_ECSEntityCount < MAX_ENTITIES, "ECSEntityCount > MAX_ENTITIES");
			ECSEntity id = m_AvailableECSEntities.front();
			m_AvailableECSEntities.pop();
			++m_ECSEntityCount;
			return id;
		}

		template<typename T, typename ... Args>
		T& AddComponent(ECSEntity entityID, Args&&... args) {

			//add component to Component array

		}

	private:
		std::queue<ECSEntity> m_AvailableECSEntities;
		uint32_t m_ECSEntityCount = 0;
	};
	
}

#endif // !_ONYX_ECS_ENTITY_REGISTRY_H_