#ifndef _ONYX_MATH_RANDOM_
#define _ONYX_MATH_RANDOM_

#include <Onyx/Core/Core.h>

namespace Onyx::Math {

	class Random {

	public:
		static uint32_t NextInt();
		static uint32_t NextInt(uint32_t max);
		static uint32_t NextInt(uint32_t min, uint32_t max);
	};
}

#endif // _ONYX_MATH_RANDOM_
