#pragma once

using namespace System;
using namespace System::Collections::Generic;

public ref class SceneNodeCLR
{
public:
	String^ Name = "NODE";
	String^ UUID = "00000000";
	List<SceneNodeCLR^>^ Nodes = gcnew List<SceneNodeCLR ^>();
};

