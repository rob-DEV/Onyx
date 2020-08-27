#include "pch.h"
#include "EditorWrapper.h"
#include <Onyx/Graphics/RendererAPI.h>
#include <Onyx/Core/Keycodes.h>

#include <Onyx/Editor/EditorInput.h>

using namespace System;
using namespace System::Drawing;
using namespace System::Runtime::InteropServices;



#include "../../../Onyx/vendor/glm/glm/glm.hpp"

namespace OnyxCLR {

	OnyxEditor::OnyxEditor()
	{
		m_Editor = new Onyx::Editor();
		for (size_t i = 0; i < 350; i++)
		{
			Onyx::EditorInput::Keys[i] = 0;
		}
	}

	OnyxEditor::~OnyxEditor()
	{

	}

	void OnyxEditor::Update()
	{
		m_Editor->OnUpdate();
	}

	
	void OnyxEditor::PollInput(array<System::Boolean>^ keys)
	{
		for (size_t i = 0; i < 350; i++)
		{
			Onyx::EditorInput::Keys[i] = keys[i];
		}
	}

	array<System::Byte>^ OnyxEditor::GetRenderedFrame()
	{
		Onyx::RenderedPixelData dd = m_Editor->GetRenderedFrame();

		//array<System::Byte> d = gcnew array< Byte >(100);
		array<System::Byte>^ dc = gcnew array<System::Byte>(dd.Size);
		// convert native pointer to System::IntPtr with C-Style cast
		Marshal::Copy((IntPtr)dd.Data, dc, 0, dd.Size);

		
		
		delete[] dd.Data;
		return dc;


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