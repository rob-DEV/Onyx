#ifndef _ONYX_ORTHOGRAPHIC_CAMERA_CONTROLLER_H_
#define _ONYX_ORTHOGRAPHIC_CAMERA_CONTROLLER_H_

#include "OrthographicCamera.h"
#include <Onyx/Core/Core.h>
#include <Onyx/Core/TimeStep.h>

namespace Onyx {

	class ONYX_API OrthographicCameraController
	{
	public:
		OrthographicCameraController();
		void OnUpdate(TimeStep timestep);
		const OrthographicCamera& GetCamera() { return m_Camera; };

	private:
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

	};

}



#endif // _ONYX_ORTHOGRAPHIC_CAMERA_H_