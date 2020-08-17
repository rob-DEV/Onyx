#ifndef _ONYX_ECS_COMPONENT_ARRAY_H_
#define _ONYX_ECS_COMPONENT_ARRAY_H_

#include "Types.h"

#include <array>

namespace Onyx {
	class IComponentArray
	{
	public:
		virtual ~IComponentArray() = default;
		virtual void EntityDestroyed(ECSEntity entity) = 0;
	};


	template<typename T>
	class ComponentArray : public IComponentArray
	{
	public:
		
	};
}
#endif // _ONYX_ECS_COMPONENT_ARRAY_H_