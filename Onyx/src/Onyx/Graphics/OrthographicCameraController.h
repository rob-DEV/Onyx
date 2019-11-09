#ifndef _ONYX_ORTHOGRAPHIC_CAMERA_CONTROLLER_H_
#define _ONYX_ORTHOGRAPHIC_CAMERA_CONTROLLER_H_

#include "OrthographicCamera.h"
#include <glm/glm.hpp>

namespace Onyx {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController();

		void onUpdate();
		
		const OrthographicCamera& getCamera() { return m_Camera; };

	private:
		OrthographicCamera m_Camera;

	};

}



#endif // _ONYX_ORTHOGRAPHIC_CAMERA_H_