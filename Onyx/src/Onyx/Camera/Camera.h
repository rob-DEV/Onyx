#ifndef _ONYX_CAMERA_H_
#define _ONYX_CAMERA_H_

#include <Onyx/Core/Core.h>

#include <glm/glm.hpp>

namespace Onyx {


	class ONYX_API Camera
	{
	public:
		virtual const glm::mat4& GetProjectionMatrix() const = 0;
		virtual const glm::mat4& GetViewMatrix() const = 0;
		virtual const glm::mat4& GetViewProjectionMatrix() const = 0;

		virtual ~Camera() {}
	
	private:

	};

}

#endif