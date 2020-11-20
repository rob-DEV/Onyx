#ifndef _ONYX_EDITOR_GIZMO_H_
#define _ONYX_EDITOR_GIZMO_H_

#include <Onyx/Core/Core.h>

#include <Onyx/Model/Model.h>


namespace Onyx {

	enum class GizmoState {
		Transform,
		Rotate,
		Scale
	};

	class ONYX_API Gizmo {
	public:
		Gizmo();
		~Gizmo();

		void SetState(GizmoState state);
		GizmoState GetState();
	private:
		Model* m_TransformModel;
		Model* m_RotateModel;
		Model* m_ScaleModel;
		
		Model* m_ActiveModel;

		GizmoState m_GizmoState = GizmoState::Transform;

		friend class EditorRenderer;
		friend class Scene;
	};

}

#endif