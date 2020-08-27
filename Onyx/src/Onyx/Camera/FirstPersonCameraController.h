#ifndef _ONYX_FP_CAMERA_CONTROLLER_H_
#define _ONYX_FP_CAMERA_CONTROLLER_H_


#include "FirstPersonPerspectiveCamera.h"

#include <Onyx/Core/Core.h>
#include <Onyx/Core/TimeStep.h>

namespace Onyx {


	class ONYX_API FirstPersonCameraController 
	{
	public:
		FirstPersonCameraController();
		void OnUpdate(Timestep timestep);
		const FirstPersonPerspectiveCamera& GetCamera() { return m_Camera; };

	private:
		float m_ZoomLevel = 1.0f;
		FirstPersonPerspectiveCamera m_Camera;
	};

}

#endif