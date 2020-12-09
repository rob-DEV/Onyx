#ifndef _ONYX_RESOURCES_UUID_H_
#define _ONYX_RESOURCES_UUID_H_

#include <Onyx/Core/Core.h>

namespace Onyx {

	class UUID {
	public:
		
		static std::string Generate(uint32_t length);

	};

}

#endif // !_ONYX_RESOURCES_UUID_H_
