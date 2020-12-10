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
		NORMAL,
		SPECULAR
	};

	struct MaterialTextures {
		Texture2D* Diffuse;
		Texture2D* Specular;
		Texture2D* Normal;
		Texture2D* NormalUp = nullptr;
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
		Material(std::string_view name);
		Material(std::string_view name, std::string_view diffuse, std::string_view specular, std::string_view normal);
		~Material();

		void Bind();

		void AddTexture(TextureParameterType type, std::string_view path);
		
		void SetName(std::string_view name) { m_Name = name; };
		std::string_view GetName() const { return m_Name; };

		void SetColor(ColorParameterType type, const glm::vec4& color);
		const glm::vec4& GetColor(ColorParameterType type);

		void SetTilingFactor(float tilingFactor) { m_TilingFactor = tilingFactor; };
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
