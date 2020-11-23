#include "onyxpch.h"
#include "Gizmo.h"
#include <Onyx/Graphics/ModelLoader.h>

namespace Onyx {

	Gizmo::Gizmo() : 
		m_TransformModel(ModelLoader::Load("TransformModel", "res/models/transform/Transform.obj")),
		m_RotateModel(ModelLoader::Load("RotateModel", "res/models/transform/Rotation.obj")),
		m_ScaleModel(ModelLoader::Load("ScaleModel", "res/models/transform/Scale.obj"))
	{
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