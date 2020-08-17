#ifndef _ONYX_ENTITY_H_
#define _ONYX_ENTITY_H_

#include <Onyx/Core/Core.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>


namespace Onyx {

	struct ONYX_API Transform
	{
		glm::vec3 Position;
		glm::quat Rotation;
		glm::vec3 Scale;

	};

	class ONYX_API Entity
	{
	public:
		Transform Transform;

	};
}


#endif