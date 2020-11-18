#include "onyxpch.h"
#include "Gizmo.h"
#include <Onyx/Model/ModelLoader.h>

namespace Onyx {

	Gizmo::Gizmo() : 
		m_TransformModel(ModelLoader::LoadFromFile("res/models/transform/Transform.obj")),
		m_RotateModel(ModelLoader::LoadFromFile("res/models/transform/Rotation.obj")),
		m_ScaleModel(ModelLoader::LoadFromFile("res/models/transform/Scale.obj"))
	{
		m_TransformModel->m_Meshes[0]->m_Color = { 1.0f,0.0f,0.0f,1.0f };
		m_TransformModel->m_Meshes[1]->m_Color = { 0.0f,1.0f,0.0f,1.0f };
		m_TransformModel->m_Meshes[2]->m_Color = { 0.0f,0.0f,1.0f,1.0f };

		m_RotateModel->m_Meshes[3]->m_Color = { 1.0f,0.0f,0.0f,1.0f };
		m_RotateModel->m_Meshes[4]->m_Color = { 0.0f,0.0f,1.0f,1.0f };
		m_RotateModel->m_Meshes[5]->m_Color = { 0.0f,1.0f,0.0f,1.0f };

		m_ScaleModel->m_Meshes[3]->m_Color = { 1.0f,0.0f,0.0f,1.0f };
		m_ScaleModel->m_Meshes[4]->m_Color = { 0.0f,0.0f,1.0f,1.0f };
		m_ScaleModel->m_Meshes[5]->m_Color = { 0.0f,1.0f,0.0f,1.0f };

		//PANELS
 		m_TransformModel->m_Meshes[3]->m_Color = { 0.5f,0.0f,0.0f,1.0f };
 		m_TransformModel->m_Meshes[4]->m_Color = { 0.5f,0.0f,0.0f,1.0f };
 		m_TransformModel->m_Meshes[5]->m_Color = { 0.5f,0.0f,0.0f,1.0f };

		m_RotateModel->m_Meshes[0]->m_Color = { 0.5f,0.0f,0.0f,1.0f };
		m_RotateModel->m_Meshes[1]->m_Color = { 0.5f,0.0f,0.0f,1.0f };
		m_RotateModel->m_Meshes[2]->m_Color = { 0.5f,0.0f,0.0f,1.0f };
 
		m_ScaleModel->m_Meshes[0]->m_Color = { 0.5f,0.0f,0.0f,1.0f };
		m_ScaleModel->m_Meshes[1]->m_Color = { 0.5f,0.0f,0.0f,1.0f };
		m_ScaleModel->m_Meshes[2]->m_Color = { 0.5f,0.0f,0.0f,1.0f };

		m_ActiveModel = m_TransformModel;
	}

	Gizmo::~Gizmo()
	{
		/*delete Transform;*/
	}

	void Gizmo::SetState(GizmoState state)
	{
		if (state == GizmoState::Transform)
			m_ActiveModel = m_TransformModel;
		else if (state == GizmoState::Rotate)
			m_ActiveModel = m_RotateModel;
		else if (state == GizmoState::Scale)
			m_ActiveModel = m_ScaleModel;
	
		m_GizmoState = state;
	}

	Onyx::GizmoState Gizmo::GetState()
	{
		return m_GizmoState;
	}

}