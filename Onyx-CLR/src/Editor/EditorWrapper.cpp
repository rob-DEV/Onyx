#include "pch.h"
#include "EditorWrapper.h"
#include <Onyx/Graphics/RendererAPI.h>


using namespace System;
using namespace System::Drawing;
using namespace System::Runtime::InteropServices;

#include "../../../Onyx/vendor/glm/glm/glm.hpp"

#include <ctime>
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