#pragma once

#include <Onyx/Onyx.h>

using namespace Onyx;

class EditorSandbox : public Layer
{
public:

	EditorSandbox();
	virtual ~EditorSandbox() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Timestep timestep) override;

private:
	Texture2D* m_Texture1;
	Mesh* m_Cube;
	Mesh* m_Cone;
	Mesh* m_FbxMeshTest;

	Scene* m_Scene;

};