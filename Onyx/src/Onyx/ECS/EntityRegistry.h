#ifndef _ONYX_ECS_ENTITY_REGISTRY_H_
#define _ONYX_ECS_ENTITY_REGISTRY_H_

#include <Onyx/Core/Core.h>

#include "Types.h"
#include "EntityView.h"
#include "ComponentArray.h"

#include <queue>
#include <unordered_map>
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
				ComponentArray<T>* f = new ComponentArray<T>();
				m_ComponentArrays.emplace(typeHash, f);
			}

			ComponentArray<T>* componentArray = (ComponentArray<T>*)m_ComponentArrays.at(typeHash);
			return componentArray->Insert(entity, std::forward<Args&&>(args)...);


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
				ECSView<T> view;
				view.data = nullptr;
				view.size = 0;
				return view;
			}
			ComponentArray<T>* componentArray = (ComponentArray<T>*)m_ComponentArrays.at(typeHash);

			ECSView<T> view;
			view.data = componentArray->m_ComponentArray.data();
			view.size = componentArray->m_Size;
			return view;
		}

		template<typename T>
		ECSView<T> GetViewOfTemplateArg(T) {

			return View<T>();
		}

		template<typename ... Ts>
		std::vector<std::tuple<Ts...>> View2()
		{
			std::vector<std::tuple<Ts...>> result = std::vector<std::tuple<Ts...>>();




			return result;
		}
		

	private:
		std::queue<ECSEntity> m_AvailableECSEntities;
		uint32_t m_ECSEntityCount = 0;

		//associative map of type hash and components
		std::unordered_map<uint64_t, IComponentArray*> m_ComponentArrays;


	};
	
}

#endif // !_ONYX_ECS_ENTITY_REGISTRY_H_