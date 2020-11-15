#include "onyxpch.h"
#include "Gizmo.h"
#include <Onyx/Model/ModelLoader.h>

namespace Onyx {

	Gizmo::Gizmo() : m_TransformModel(ModelLoader::LoadFromFile("res/models/transform.obj"))
	{
		m_TransformModel->m_Meshes[0]->m_Color = { 1.0f,0.0f,0.0f,1.0f };
		m_TransformModel->m_Meshes[1]->m_Color = { 0.0f,1.0f,0.0f,1.0f };
		m_TransformModel->m_Meshes[2]->m_Color = { 0.0f,0.0f,1.0f,1.0f };

		//PANELS
		m_TransformModel->m_Meshes[3]->m_Color = { 0.5f,0.0f,0.0f,1.0f };
		m_TransformModel->m_Meshes[4]->m_Color = { 0.5f,0.0f,0.0f,1.0f };
		m_TransformModel->m_Meshes[5]->m_Color = { 0.5f,0.0f,0.0f,1.0f };
	}

	Gizmo::~Gizmo()
	{
		/*delete Transform;*/
	}

}