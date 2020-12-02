#include "onyxpch.h"
#include "Material.h"
#include "Shader.h"

#include <Onyx/Resources/Hasher.h>
#include <Onyx/Core/Application.h>
#include <Onyx/Resources/TextureCache.h>

namespace Onyx {

	Material::Material() :
		m_Name("DEFAULT")
	{
		if (Application::Get()->GetContext() == ApplicationContext::Runtime)
			m_Shader = ShaderCache::Get("3DRuntime");
		else
			m_Shader = ShaderCache::Get("3DEditor");

		CreateDefaultNamedMaterial();
	}

	Material::Material(std::string_view name) :
		m_Name(name)
	{
		if (Application::Get()->GetContext() == ApplicationContext::Runtime)
			m_Shader = ShaderCache::Get("3DRuntime");
		else
			m_Shader = ShaderCache::Get("3DEditor");
		CreateDefaultNamedMaterial();
	}

	Material::Material(std::string_view name, std::string_view diffuse, std::string_view specular, std::string_view normal)
	{
		m_Name = name;

		m_TilingFactor = 1.0;
	}




	Material::~Material()
	{

	}

	void Material::Bind()
	{
		m_Shader->Bind();
		//Set uniform colors
		m_Shader->SetFloat4("u_Material.ambient", m_Colors.Ambient);
		m_Shader->SetFloat4("u_Material.diffuse", m_Colors.Diffuse);
		m_Shader->SetFloat4("u_Material.specular", m_Colors.Specular);


		//Bind texture samplers
		uint32_t diffuse = 0;
		uint32_t spec = 1;
		uint32_t normal = 2;

		m_Textures.Diffuse->Bind(diffuse);

		m_Shader->SetInt("u_Material.diffuseTex", diffuse);

		//Set tiling factor
		m_Shader->SetFloat("u_Material.tilingFactor", m_TilingFactor);


	}

	void Material::AddTexture(TextureParameterType type, std::string_view path)
	{
		//Grab/Add the texture from/to the cache
		Texture2D* texture = nullptr;

		if (TextureCache::Get().Exists(path)) {
			texture = (Texture2D*)TextureCache::Get().GetTexture(path);
		}
		else {
			texture = (Texture2D*)TextureCache::Get().CacheTexture(path);
		}

		switch (type)
		{
		case TextureParameterType::DIFFUSE:
			m_Textures.Diffuse = texture;
			break;
		case TextureParameterType::SPECULAR:
			m_Textures.Specular = texture;
			break;
		case TextureParameterType::NORMAL:
			m_Textures.Normal = texture;
			break;
		default:
			printf("ERROR: Invalid MaterialParameterType!\n");
			assert(false);
			break;
		}
	}

	void Material::SetColor(ColorParameterType type, const glm::vec4& color)
	{
		switch (type)
		{
		case ColorParameterType::AMBIENT:
			m_Colors.Ambient = color;
			break;
		case ColorParameterType::DIFFUSE:
			m_Colors.Diffuse = color;
			break;
		case ColorParameterType::SPECULAR:
			m_Colors.Specular = color;
			break;
		default:
			printf("ERROR: Invalid MaterialTextureType!\n");
			assert(false);
			break;
		}
	}

	void Material::CreateDefaultNamedMaterial()
	{
		//Creates a white material with a white (cached) texture

		Texture2D* defaultTexture = nullptr;

		if (TextureCache::Get().Exists("DEFAULT_MATERIAL_TEXTURE")) {
			defaultTexture = (Texture2D*)TextureCache::Get().GetTexture("DEFAULT_MATERIAL_TEXTURE");
		}
		else {
			defaultTexture = (Texture2D*)TextureCache::Get().CacheTexture("DEFAULT_MATERIAL_TEXTURE", 1, 1);
			uint32_t pureWhiteTexture = 0xffffffff;
			defaultTexture->SetData(&pureWhiteTexture, sizeof(uint32_t));
		}

		m_Textures.Diffuse = defaultTexture;
		m_Textures.Normal = defaultTexture;
		m_Textures.Specular = defaultTexture;

		m_Colors.Ambient = glm::vec4(1.0f);
		m_Colors.Diffuse = glm::vec4(1.0f);
		m_Colors.Specular = glm::vec4(1.0f);

		m_TilingFactor = 1.0;

	}
}