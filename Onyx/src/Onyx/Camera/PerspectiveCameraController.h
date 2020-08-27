#ifndef _ONYX_PERSPECTIVE_CAMERA_CONTROLLER_H_
#define _ONYX_PERSPECTIVE_CAMERA_CONTROLLER_H_


#include "PerspectiveCamera.h"

#include <Onyx/Core/Core.h>
#include <Onyx/Core/TimeStep.h>

namespace Onyx {


	class ONYX_API PerspectiveCameraController 
	{
	public:
		PerspectiveCameraController();
		void OnUpdate(Timestep timestep);
		const PerspectiveCamera& GetCamera() { return m_Camera; };

	private:
		float m_ZoomLevel = 1.0f;
		PerspectiveCamera m_Camera;
	};

}

#endif