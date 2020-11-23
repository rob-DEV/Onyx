#ifndef _ONYX_GRAPHICS_VERTEX_H_
#define _ONYX_GRAPHICS_VERTEX_H_

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace Onyx {

	struct Vertex3D
	{
		Vertex3D() = default;

		Vertex3D(const glm::vec3 & position, const glm::vec2 & texcoords) : 
			Position(position),
			TexCoords(texcoords),
			Color(glm::vec4(1.0f))
		{
		}

		Vertex3D(const glm::vec3 & position, const glm::vec2 & texcoords, const glm::vec3 & normal) : 
			Position(position),
			TexCoords(texcoords),
			Color(glm::vec4(1.0f)),
			Normal(normal) {
		}

		Vertex3D(const glm::vec3 & position, const glm::vec2 & texcoords, const glm::vec3 & normal, const glm::vec3 & tangent) :
			Position(position),
			TexCoords(texcoords),
			Normal(normal),
			Color(glm::vec4(1.0f)),
			Tangent(tangent) {
		}

		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoords;
		glm::vec3 Normal;
		glm::vec3 Tangent;
	};



}

#endif