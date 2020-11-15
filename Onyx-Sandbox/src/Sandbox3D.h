#pragma once

#include <Onyx/Onyx.h>

using namespace Onyx;
namespace Onyx {
	class Scene;
}
class Sandbox3D : public Layer
{
public:

	Sandbox3D();
	virtual ~Sandbox3D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Timestep timestep) override;

private:
	Texture2D* m_Texture1;
	Mesh* m_Cube;
	Mesh* m_Cone;
	Mesh* m_FbxMeshTest;

	Onyx::Scene* m_Scene;

};