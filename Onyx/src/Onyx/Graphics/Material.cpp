#include "onyxpch.h"
#include "Material.h"
#include "Shader.h"

namespace Onyx {

	Material::Material()
	{
		Texture2D* defaultTexture = Texture2D::Create(1, 1);
		uint32_t pureWhiteTexture = 0xffffffff;
		defaultTexture->SetData(&pureWhiteTexture, sizeof(uint32_t));
		
		m_Textures[0] = defaultTexture;
		m_Textures[1] = defaultTexture;
		m_Textures[2] = defaultTexture;

		m_Colors[0] = glm::vec4(0.1f);
		m_Colors[1] = glm::vec4(0.8f,0.0f,0.5f,1.0f);
		m_Colors[2] = glm::vec4(1.0f);
	}
	
	Material::Material(const std::string& diffuse, const std::string& specular, const std::string& normal)
	{
		m_Textures[0] = Texture2D::Create(diffuse);
		m_Textures[2] = Texture2D::Create(specular);
		m_Textures[1] = Texture2D::Create(normal);

		m_Colors[0] = glm::vec4(1.0f);
		m_Colors[1] = glm::vec4(1.0f);
		m_Colors[2] = glm::vec4(1.0f);
	}


	Material::~Material()
	{
		//TODO: Consider texture cache
		//for (auto t : m_Textures)
			//delete t;
	}

	void Material::Bind(Shader* shader)
	{
		//Color order order
		//AMBIENT = 0,
		//DIFFUSE,
		//SPECULAR,

		shader->SetFloat4("u_Material.ambient", m_Colors[0]);
		shader->SetFloat4("u_Material.diffuse", m_Colors[1]);
		shader->SetFloat4("u_Material.specular", m_Colors[2]);

	}

	void Material::AddTexture(TextureParameterType type, const std::string& path)
	{
		switch (type)
		{
		case TextureParameterType::DIFFUSE:
			m_Textures[0] = Texture2D::Create(path);
			break;
		case TextureParameterType::SPECULAR:
			m_Textures[1] = Texture2D::Create(path);
			break;
		case TextureParameterType::NORMAL:
			m_Textures[2] = Texture2D::Create(path);
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
			m_Colors[0] = color;
			break;
		case ColorParameterType::DIFFUSE:
			m_Colors[1] = color;
			break;
		case ColorParameterType::SPECULAR:
			m_Colors[2] = color;
			break;
		default:
			printf("ERROR: Invalid MaterialTextureType!\n");
			assert(false);
			break;
		}
	}

}