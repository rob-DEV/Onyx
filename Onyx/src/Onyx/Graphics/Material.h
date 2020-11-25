#ifndef _ONYX_GRAPHICS_MATERIAL_H_
#define _ONYX_GRAPHICS_MATERIAL_H_

#include <string>
#include <array>
#include <glm/glm.hpp>

#include "Texture.h"

namespace Onyx {
	
	class Shader;

	enum class ColorParameterType {
		AMBIENT = 0,
		DIFFUSE,
		SPECULAR,
	};

	enum class TextureParameterType {
		DIFFUSE = 0,
		SPECULAR,
		NORMAL
	};

	class Material
	{

	public:
		Material();
		Material(const std::string& diffuse, const std::string& specular, const std::string& normal);
		~Material();

		void Bind(Shader* shader);

		void AddTexture(TextureParameterType type, const std::string& path);
		void SetColor(ColorParameterType type, const glm::vec4& color);
		void SetTilingFactor(float tilingFactor) { m_TilingFactor = tilingFactor; };

	private:
		std::string m_Name;
		
		//Texture order
		//AMBIENT = 0,
		//DIFFUSE,
		//SPECULAR,
		std::array<Texture2D*, 3> m_Textures;

		//Color order order
		//AMBIENT = 0,
		//DIFFUSE,
		//SPECULAR,
		std::array<glm::vec4, 3> m_Colors;

		float m_TilingFactor;

	};

}

#endif // !_ONYX_GRAPHICS_MATERIAL_H_
