#include "onyxpch.h"
#include "SceneSerializer.h"

#include <tinyxml2.h>

#include <sstream>
#include <string>


#include <Onyx/Graphics/ModelLoader.h>

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

namespace Onyx {

	using namespace tinyxml2;

	bool SceneSerializer::Serialize(Scene* scene, std::string_view filePath) {

		tinyxml2::XMLDocument xmlDoc;
		
		XMLNode* pRoot = xmlDoc.NewElement("ONYX-SCENE");
		((XMLElement*)pRoot)->SetAttribute("UniqueIdentifier", scene->m_SceneData.Identifier.c_str());
		((XMLElement*)pRoot)->SetAttribute("Name", scene->m_SceneData.Name.c_str());
		xmlDoc.InsertFirstChild(pRoot);

		//Process each entity in the scene along with it's components
		for (auto e : scene->m_Entities) {

			XMLElement* pEntityElement = xmlDoc.NewElement("ONYX-ENTITY");

			if (e->HasComponent<TagComponent>()) {
				
				TagComponent& t = e->GetComponent<TagComponent>();
				XMLElement* pTagElement = xmlDoc.NewElement("TagComponent");
				pTagElement->SetText(t.Tag.c_str());

				pEntityElement->InsertEndChild(pTagElement);

			}

			if (e->HasComponent<TransformComponent>()) {
				
				TransformComponent& t = e->GetComponent<TransformComponent>();
				XMLElement* pTransformElement = xmlDoc.NewElement("TransformComponent");
				XMLElement* pTransformPositionElement = xmlDoc.NewElement("Position");

				for (uint8_t i = 0; i < 3; ++i)
				{
					char x[2] = { 'X', 0 };
					x[0] = 'X' + i;

					XMLElement* pVec3Element = xmlDoc.NewElement(x);
					pVec3Element->SetText(t.Position[i]);

					pTransformPositionElement->InsertEndChild(pVec3Element);
				}

				pTransformElement->InsertEndChild(pTransformPositionElement);

				pEntityElement->InsertEndChild(pTransformElement);

			}

			pRoot->InsertEndChild(pEntityElement);
		}

		if (xmlDoc.SaveFile(filePath.data()) == 0)
			return true;
		
		return false;
	}

	Scene* SceneSerializer::DeSerialize(std::string_view filePath) {
		
		tinyxml2::XMLDocument xmlDoc;

		xmlDoc.LoadFile(filePath.data());

		XMLNode* pRoot = xmlDoc.FirstChild();

		if (pRoot == nullptr) {
			ONYX_ERROR("Scene Serializer ERROR: XML is Invalid!");
			return nullptr;
		}

		const char* sceneIdentifer = ((XMLElement*)pRoot)->Attribute("UniqueIdentifier");
		const char* sceneName = ((XMLElement*)pRoot)->Attribute("Name");

		
		if (sceneIdentifer == nullptr || strlen(sceneIdentifer) < 10) {
			ONYX_ERROR("Scene Serializer ERROR: Failed to find a valid Scene!");
			return nullptr;
		}

		//Iterate through serialized entities
		XMLElement* pEntityElement = pRoot->FirstChildElement("ONYX-ENTITY");
		
		Scene* scene = new Scene(SceneData(sceneName, filePath.data(), sceneIdentifer));
		
		while (pEntityElement != nullptr) {

			SceneNode* entity = scene->CreateEntity();


			XMLElement* pEntityComponentElement = pEntityElement->FirstChildElement();

			while (pEntityComponentElement != nullptr) {

				//Determine component type and De-Serialize
				if (_stricmp(pEntityComponentElement->Value(), "TagComponent") == 0) {
					
					TagComponent t = TagComponent(pEntityComponentElement->GetText());
					entity->GetEntity()->AddComponent<TagComponent>(t);
					entity->SetName(t.Tag);
					
				}
				else if (_stricmp(pEntityComponentElement->Value(), "TransformComponent") == 0) {

					TransformComponent t = TransformComponent();
					
					XMLElement* pTransformPositionElement = pEntityComponentElement->FirstChildElement("Position");
					pTransformPositionElement->FirstChildElement("X")->QueryFloatText(&t.Position.x);
					pTransformPositionElement->FirstChildElement("Y")->QueryFloatText(&t.Position.y);
					pTransformPositionElement->FirstChildElement("Z")->QueryFloatText(&t.Position.z);

					XMLElement* pTransformRotationElement = pEntityComponentElement->FirstChildElement("Rotation");
					pTransformRotationElement->FirstChildElement("X")->QueryFloatText(&t.Rotation.x);
					pTransformRotationElement->FirstChildElement("Y")->QueryFloatText(&t.Rotation.y);
					pTransformRotationElement->FirstChildElement("Z")->QueryFloatText(&t.Rotation.z);

					XMLElement* pTransformScaleElement = pEntityComponentElement->FirstChildElement("Scale");
					pTransformScaleElement->FirstChildElement("X")->QueryFloatText(&t.Scale.x);
					pTransformScaleElement->FirstChildElement("Y")->QueryFloatText(&t.Scale.y);
					pTransformScaleElement->FirstChildElement("Z")->QueryFloatText(&t.Scale.z);

					entity->GetEntity()->AddComponent<TransformComponent>(t);

				}
				else if (_stricmp(pEntityComponentElement->Value(), "ModelComponent") == 0) {

					//Preparing for multiple meshes per entity
					SceneNode* modelEntity = scene->CreateEntity(entity);

					MeshRendererComponent m = MeshRendererComponent();

					XMLElement* pMeshName= pEntityComponentElement->FirstChildElement("ModelName");
					XMLElement* pMeshPath = pEntityComponentElement->FirstChildElement("ModelPath");
					XMLElement* pIsStatic = pEntityComponentElement->FirstChildElement("IsStatic");

					const char* meshName = pMeshName->GetText();
					const char* meshFilePath = pMeshPath->GetText();
					bool meshStatic = false;
					pIsStatic->QueryBoolText(&meshStatic);

					Model* model = ModelLoader::Load(meshName, meshFilePath);
					m.Meshes = model->GetMeshes();

					modelEntity->SetName(meshName);
					modelEntity->GetEntity()->AddComponent<MeshRendererComponent>(m);
					modelEntity->GetEntity()->m_Static = meshStatic;

					TransformComponent t = TransformComponent();
					
					//TODO: Refactor duplicated code
					XMLElement* pTransformComponentElement = pEntityComponentElement->FirstChildElement("TransformComponent");
					
					XMLElement* pTransformPositionElement = pTransformComponentElement->FirstChildElement("Position");
					pTransformPositionElement->FirstChildElement("X")->QueryFloatText(&t.Position.x);
					pTransformPositionElement->FirstChildElement("Y")->QueryFloatText(&t.Position.y);
					pTransformPositionElement->FirstChildElement("Z")->QueryFloatText(&t.Position.z);

					XMLElement* pTransformRotationElement = pTransformComponentElement->FirstChildElement("Rotation");
					pTransformRotationElement->FirstChildElement("X")->QueryFloatText(&t.Rotation.x);
					pTransformRotationElement->FirstChildElement("Y")->QueryFloatText(&t.Rotation.y);
					pTransformRotationElement->FirstChildElement("Z")->QueryFloatText(&t.Rotation.z);

					XMLElement* pTransformScaleElement = pTransformComponentElement->FirstChildElement("Scale");
					pTransformScaleElement->FirstChildElement("X")->QueryFloatText(&t.Scale.x);
					pTransformScaleElement->FirstChildElement("Y")->QueryFloatText(&t.Scale.y);
					pTransformScaleElement->FirstChildElement("Z")->QueryFloatText(&t.Scale.z);

					modelEntity->GetEntity()->AddComponent<TransformComponent>(t);

				}
				pEntityComponentElement = pEntityComponentElement->NextSiblingElement();
			}

			pEntityElement = pEntityElement->NextSiblingElement("ONYX-ENTITY");
		}

		return scene;
	}

}