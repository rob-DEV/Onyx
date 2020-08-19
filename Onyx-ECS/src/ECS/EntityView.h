#ifndef _ONYX_ECS_ENTITY_VIEW_H_
#define _ONYX_ECS_ENTITY_VIEW_H_

#include <Onyx/Core/Core.h>
#include <tuple>

namespace Onyx {

	template<class... Types>
	class ECSView
	{
	public:

		//----------

		std::vector< std::tuple<Types*...>> sets;

		//ITERATOR IMPLEMENTATION
		//EXTRACT TUPLE DATA

	};



}

#endif