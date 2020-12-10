#include "onyxpch.h"
#include "Material.h"
#include "Shader.h"

#include <Onyx/Core/Input.h>
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
		uint32_t normal = 1;
		uint32_t spec = 2;

		m_Textures.Diffuse->Bind(diffuse);
		
		static bool normals = true;
		
		//Toggle normal map
		if (Input::IsKeyPressed(ONYX_KEY_N))
			normals = (normals + 1) % 2;


		if(normals)
			m_Textures.Normal->Bind(normal);
		else
			m_Textures.NormalUp->Bind(normal);

		
		//Set textures
		m_Shader->SetInt("u_Material.diffuseTex", diffuse);
		m_Shader->SetInt("u_Material.normalTex", normal);

		//Set colors
		m_Shader->SetFloat4("u_Material.ambient", m_Colors.Ambient);
		m_Shader->SetFloat4("u_Material.diffuse", m_Colors.Diffuse);
		m_Shader->SetFloat4("u_Material.specular", m_Colors.Specular);

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
		case TextureParameterType::NORMAL:
			m_Textures.Normal = texture;
			break;
		case TextureParameterType::SPECULAR:
			m_Textures.Specular = texture;
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

	const glm::vec4& Material::GetColor(ColorParameterType type)
	{
		switch (type)
		{
		case ColorParameterType::AMBIENT:
			return m_Colors.Ambient;
			break;
		case ColorParameterType::DIFFUSE:
			return m_Colors.Diffuse;
			break;
		case ColorParameterType::SPECULAR:
			return m_Colors.Specular;
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

		//Up normal map
		if (TextureCache::Get().Exists("res/textures/default/normal_up.png")) {
			m_Textures.NormalUp = (Texture2D*)TextureCache::Get().GetTexture("res/textures/default/normal_up.png");
		}
		else {
			m_Textures.NormalUp = (Texture2D*)TextureCache::Get().CacheTexture("res/textures/default/normal_up.png");
		}
	}
}