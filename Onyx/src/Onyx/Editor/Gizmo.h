#ifndef _ONYX_EDITOR_GIZMO_H_
#define _ONYX_EDITOR_GIZMO_H_

#include <Onyx/Core/Core.h>



namespace Onyx {

	class Model;

	class ONYX_API Gizmo {
	public:
		Gizmo();
		~Gizmo();
		Model* m_TransformModel;
		Model* m_RotateModel;
		Model* m_ScaleModel;

		Model* m_ActiveModel = m_TransformModel;
	};

}

#endif