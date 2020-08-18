#ifndef _ONYX_ECS_COMPONENT_ARRAY_H_
#define _ONYX_ECS_COMPONENT_ARRAY_H_

#include "Types.h"

#include <array>
#include <algorithm>
#include <unordered_map>
#include <cassert>

namespace Onyx {
	class IComponentArray
	{
	public:
		virtual ~IComponentArray() {
		
			printf("DESTROYED IComponentArray");
		
		}
		virtual void EntityDestroyed(ECSEntity entity) = 0;

#if _ONYX_DEBUG_
		std::string DEBUG_NAME;
#endif
	
	};



	//Array allocated per Component type basis
	template<typename T>
	class ComponentArray : public IComponentArray
	{
	public:
		ComponentArray<T>()
		{
			#if _ONYX_DEBUG_
			DEBUG_NAME = typeid(T).name();
			printf("Setup ComponentArray of type %s\n\n", DEBUG_NAME.c_str());
			#endif
		}

		ComponentArray<T>(const ComponentArray<T>& other)
		{
			printf("COPIED!\n");
		}

		~ComponentArray<T>()
		{
			printf("DESTROYED!\n");
		}


		T& Insert(ECSEntity entity, T component)
		{
			#if _ONYX_DEBUG_
			printf("Inserting Component of Type %s, ComponentArray of type %s\n\n", typeid(T).name(), DEBUG_NAME.c_str());
			#endif
			assert(m_Size < MAX_ENTITIES, "Adding Component to full ComponentArray");

			if (m_EntityToIndexMap.find(entity) != m_EntityToIndexMap.end())
			{
				assert(false, "Entity already has Component");
			}

			//insert the component and increment m_Size
			m_EntityToIndexMap[entity] = m_Size;
			m_ComponentArray[m_EntityToIndexMap[entity]] = component;
			m_IndexToEntityMap[m_Size] = entity;
			
			++m_Size;
			return m_ComponentArray[m_EntityToIndexMap[entity]];
		}

		void Remove(ECSEntity entity) 
		{
			#if _ONYX_DEBUG_
			printf("Removing Component of Type %s, ComponentArray of type %s\n\n", typeid(T).name(), DEBUG_NAME.c_str());
			#endif
			if (m_EntityToIndexMap.find(entity) != m_EntityToIndexMap.end())
			{
				uint32_t indexToCompInComponentArray = m_EntityToIndexMap[entity];
				
				//Take the last element in the ComponentArray and swap with the removed Component
				//to keep the underlying memory contiguous
				//Update map references

				ECSEntity lastComponentEntity = m_IndexToEntityMap[m_ComponentArray.size() - 1 + m_Size];

				m_ComponentArray[indexToCompInComponentArray] = *(m_ComponentArray.end() - 1);

				m_EntityToIndexMap[lastComponentEntity] = indexToCompInComponentArray;
				m_EntityToIndexMap.erase(entity);
				m_IndexToEntityMap[indexToCompInComponentArray = lastComponentEntity];

				--m_Size;

				return;
			}


			assert(false, "Entity does not have this Component");

		}

		T& Get(ECSEntity entity) 
		{
			#if _ONYX_DEBUG_
			printf("Getting Component of Type %s, ComponentArray of type %s\n\n", typeid(T).name(), DEBUG_NAME.c_str());
			#endif
			if (m_EntityToIndexMap.find(entity) != m_EntityToIndexMap.end())
			{
				return m_ComponentArray.at(m_EntityToIndexMap[entity]);
			}

			assert(false, "Entity does not have this Component");
		}

		void EntityDestroyed(ECSEntity entity) override
		{
		
		}


		std::unordered_map<ECSEntity, uint32_t> m_EntityToIndexMap;
		std::unordered_map<ECSEntity, uint32_t> m_IndexToEntityMap;
		//Actual array of components accessed via ECSEntity ID
		std::array<T, MAX_ENTITIES> m_ComponentArray;

		uint32_t m_Size = 0;

		friend class ECSEntityRegistry;
	};
}
#endif // _ONYX_ECS_COMPONENT_ARRAY_H_