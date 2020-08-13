#pragma once

#include <Onyx/Core/Layer.h>
#include <Onyx/Graphics/Texture.h>
#include <Onyx/Graphics/OrthographicCameraController.h>

using namespace Onyx;

class Sandbox3D : public Onyx::Layer
{
public:

	Sandbox3D();
	virtual ~Sandbox3D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(TimeStep timestep) override;

private:
	OrthographicCameraController* m_CameraController;
	Texture2D* m_Texture1;

};