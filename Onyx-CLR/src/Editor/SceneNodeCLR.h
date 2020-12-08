#pragma once

using namespace System;
using namespace System::Collections::Generic;

public ref class SceneNodeCLR
{
public:
	String^ Name = "NODE";
	List<SceneNodeCLR^>^ Nodes = gcnew List<SceneNodeCLR ^>();
};

