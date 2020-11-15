#include "pch.h"
#include "Editor.h"
#include <Onyx/Graphics/RendererAPI.h>
#include <Onyx/Core/Keycodes.h>

#include <Onyx/Editor/EditorInput.h>

using namespace System;
using namespace System::Drawing;
using namespace System::Runtime::InteropServices;


#include <glm/glm.hpp>

namespace OnyxCLR {

	OnyxEditor::OnyxEditor()
	{
		m_Editor = new Onyx::Editor();
	}

	OnyxEditor::~OnyxEditor()
	{
		
	}

	void OnyxEditor::Update()
	{
		m_Editor->OnUpdate();
	}


	void OnyxEditor::UpdateEngineInput(array<System::Boolean>^ keys, array<System::Boolean>^ mouseButtons, System::Drawing::Point mousePosition)
	{
		for (size_t i = 0; i < 350; i++)
			m_Editor->GetInputKeyBuffer()[i] = keys[i];
		
		for (size_t i = 0; i < 8; i++)
			m_Editor->GetInputMouseButtonBuffer()[i] = mouseButtons[i];


		m_Editor->SetMousePosition(mousePosition.X, mousePosition.Y);
	}

	void OnyxEditor::GetRenderedFrame(int* buffer)
	{
		Onyx::RenderedPixelData dd = m_Editor->GetRenderedFrame();

		int pos = 0;
		for (int i = 0; i < 1280 * 720; ++i)
		{
			buffer[i] = (255 << 24) + ((unsigned char)dd.Data[pos] << 16) + ((unsigned char)dd.Data[pos + 1] << 8) + (unsigned char)dd.Data[pos + 2];
			pos += 3;
		}
	}

	void OnyxEditor::OpenScene(System::String^ filePath)
	{

	}

	void OnyxEditor::SaveScene(System::String^ filePath)
	{

	}

	void OnyxEditor::CreateEntity(float x, float y, float z)
	{
		m_Editor->CreateEntity(glm::vec3(x,y,z));
	}

}