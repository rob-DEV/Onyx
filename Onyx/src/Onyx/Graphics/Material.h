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

	struct MaterialTextures {
		Texture2D* Diffuse;
		Texture2D* Specular;
		Texture2D* Normal;
	};

	struct MaterialColors {
		glm::vec4 Ambient;
		glm::vec4 Diffuse;
		glm::vec4 Specular;
	};

	class Material
	{

	public:
		Material();
		Material(const std::string& name);
		Material(const std::string& name, const std::string& diffuse, const std::string& specular, const std::string& normal);
		~Material();

		void Bind();

		void AddTexture(TextureParameterType type, const std::string& path);
		void SetColor(ColorParameterType type, const glm::vec4& color);
		void SetTilingFactor(float tilingFactor) { m_TilingFactor = tilingFactor; };
		const std::string& GetName() const { return m_Name; };
		void SetName(const std::string& name) { m_Name = name; };


	private:
		std::string m_Name;
		Shader* m_Shader;
		void CreateDefaultNamedMaterial();

		MaterialTextures m_Textures;
		MaterialColors m_Colors;

		float m_TilingFactor;

	};

}

#endif // !_ONYX_GRAPHICS_MATERIAL_H_
