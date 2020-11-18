#pragma once

#include <Onyx/Entity/Components.h>

using namespace System::Runtime::InteropServices;

public ref class TagComponent
{
	TagComponent(System::String^ name)
	{
		m_Component->Tag = (char*)(void*)Marshal::StringToHGlobalAnsi(name);
	}

private:
	Onyx::TagComponent* m_Component;

};