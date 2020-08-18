#ifndef _ONYX_ECS_ENTITY_REGISTRY_H_
#define _ONYX_ECS_ENTITY_REGISTRY_H_

#include <Onyx/Core/Core.h>

#include "Types.h"
#include "ComponentArray.h"

#include <queue>

#include <cassert>

namespace Onyx {

	inline unsigned long long hash(const char* str)
	{
		unsigned long long results = 0x898324; //  anything but 0 is probably OK.
		for (int current = 0; current != strlen(str); ++current) {
			results = 127 * results + static_cast<unsigned char>(str[current]);
		}
		return results;
	}

	template<typename T>
	struct ECSView {
		T* data;
		uint32_t size;
	};

	class ECSEntityRegistry {
	public:
		ECSEntityRegistry() 
		{
			for (ECSEntity entity = 0; entity < MAX_ENTITIES; ++entity)
			{
				m_AvailableECSEntities.push(entity);
			}
		};
		~ECSEntityRegistry() {}

		ECSEntity Create() 
		{
			assert(m_ECSEntityCount < MAX_ENTITIES, "ECSEntityCount > MAX_ENTITIES");
			ECSEntity id = m_AvailableECSEntities.front();
			m_AvailableECSEntities.pop();
			++m_ECSEntityCount;
			return id;

		}


		template<typename T, typename ... Args>
		T& AddComponent(ECSEntity entity, Args&&... args) 
		{
			//Add component to Component array
			uint64_t typeHash = hash(typeid(T).name());
			std::unordered_map<uint64_t, IComponentArray*>::const_iterator got = m_ComponentArrays.find((uint64_t)typeHash);

			if (got == m_ComponentArrays.end()) {
				//Create the Component Array should it not already exist
				m_ComponentArrays.emplace(typeHash, new ComponentArray<T>());
			}

			ComponentArray<T>* componentArray = (ComponentArray<T>*)m_ComponentArrays.at(typeHash);
			return componentArray->Insert(entity, T(args ...));


		}

		template<typename T, typename ... Args>
		T& GetComponent(ECSEntity entity)
		{

			//Add component to Component array
			uint64_t typeHash = hash(typeid(T).name());
			std::unordered_map<uint64_t, IComponentArray*>::const_iterator got = m_ComponentArrays.find((uint64_t)typeHash);

			if (got == m_ComponentArrays.end()) {
				//Create the Component Array should it not already exist
				assert(false, "No valid ComponentArray found");
			}

			ComponentArray<T>* componentArray = (ComponentArray<T>*)m_ComponentArrays.at(typeHash);
			return componentArray->Get(entity);

		
		}

		template<typename T, typename ... Args>
		void RemoveComponent(ECSEntity entity)
		{

			//Add component to Component array
			uint64_t typeHash = hash(typeid(T).name());
			std::unordered_map<uint64_t, IComponentArray*>::const_iterator got = m_ComponentArrays.find((uint64_t)typeHash);

			if (got == m_ComponentArrays.end()) {
				//Create the Component Array should it not already exist
				assert(false, "No valid ComponentArray found");
			}

			ComponentArray<T>* componentArray = (ComponentArray<T>*)m_ComponentArrays.at(typeHash);
			return componentArray->Remove(entity);


		}

		template<typename T>
		ECSView<T> View() 
		{
			uint64_t typeHash = hash(typeid(T).name());
			std::unordered_map<uint64_t, IComponentArray*>::const_iterator got = m_ComponentArrays.find((uint64_t)typeHash);

			if (got == m_ComponentArrays.end()) {
				//Create the Component Array should it not already exist
				assert(false, "No valid ComponentArray found");
			}

			ComponentArray<T>* componentArray = (ComponentArray<T>*)m_ComponentArrays.at(typeHash);
			//T* ptr = componentArray->m_ComponentArray.data();
			//ECSView<T> v;
			//v.data = ptr;
			//v.size = componentArray->m_Size;
			return ECSView<T>();
		}
		

	private:
		std::queue<ECSEntity> m_AvailableECSEntities;
		uint32_t m_ECSEntityCount = 0;

		//associative map of type hash and components
		std::unordered_map<uint64_t, IComponentArray*> m_ComponentArrays;


	};
	
}

#endif // !_ONYX_ECS_ENTITY_REGISTRY_H_