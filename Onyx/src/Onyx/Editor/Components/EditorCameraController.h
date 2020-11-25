#ifndef _ONYX_EDITOR_CAMERA_H_
#define _ONYX_EDITOR_CAMERA_H_

#include <Onyx/Core/Core.h>
#include <Onyx/Core/TimeStep.h>
#include <Onyx/Camera/PerspectiveCamera.h>

namespace Onyx {

	class ONYX_API EditorCameraController {
	public:
		EditorCameraController();
		~EditorCameraController();

		void OnUpdate(Timestep ts);
		const Camera& GetCamera() const { return m_Camera; };

	private:
		PerspectiveCamera m_Camera;
		float m_MovementSpeed = 0.1f;
	};
}

#endif // !_ONYX_EDITOR_CAMERA_H_
