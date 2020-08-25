#ifndef _ONYX_REGISTRY_H_
#define _ONYX_REGISTRY_H_

#include <Onyx/Core/Core.h>

namespace Onyx {

	class Scene;

	class ONYX_API Registry {
	public:

		Registry();
		uint32_t Create();

	private:
		void* m_Registry;

		friend class Entity;
	};


}

#endif