#ifndef _ONYX_PHYSICS_H_
#define _ONYX_PHYSICS_H_

#include <Onyx/Core/Core.h>

#include <glm/glm.hpp>

namespace Onyx {


	class ONYX_API Ray
	{
	public:
	
		Ray(glm::vec3 origin, glm::vec3 direction) {
			//Calculate a ray vector based on origin and direction
			m_Origin = origin;
			m_Ray = glm::normalize(direction);

		}

		//Computes position in world space of a point distance units along the Ray
		glm::vec3 GetPoint(float distance) {

			glm::vec3 scaledRay = glm::vec3(m_Ray.x * distance, m_Ray.y * distance, m_Ray.z * distance);
			glm::vec3 point = m_Origin + scaledRay;

			return point;
		}
	

	private:
		glm::vec3 m_Ray;
		glm::vec3 m_Origin;


	};


}

#endif