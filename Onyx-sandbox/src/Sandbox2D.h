#pragma once

#include <Onyx/Core/Layer.h>
#include <Onyx/Graphics/Texture.h>
#include <Onyx/Graphics/OrthographicCameraController.h>

using namespace Onyx;

class Sandbox2D : public Onyx::Layer
{
public:

	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate() override;

private:
	OrthographicCameraController* m_CameraController;
	Texture2D* m_Texture1;
	Texture2D* m_Texture2;

};