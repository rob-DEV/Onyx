#ifndef _ONYX_SCENE_H_
#define _ONYX_SCENE_H_

#include <Onyx/Core/Core.h>
#include <Onyx/Scene/Entity.h>


namespace Onyx {

	class ONYX_API Scene {


	private:
		//TODO: Move away from std::vector
		std::vector<Entity*> m_Entities;
	};


}

#endif