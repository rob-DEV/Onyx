#pragma once

#include <Onyx/Entity/Components.h>

using namespace System::Runtime::InteropServices;


#include <Engine/Vector.h>


namespace OnyxCLR {

	public enum class ComponentType
	{
		TagComponent,
		TransformComponent,
		MeshRendererComponent,
	};

	public ref class Component {
	public:
		ComponentType Type;
	};

	public ref class TagComponent : public Component {

	public:
		System::String^ Tag = gcnew System::String("");

		TagComponent(System::String^ tag)
		{
			this->Type = ComponentType::TagComponent;
			this->Tag = tag;
		}
	};

	public ref class TransformComponent : public Component {

	public:
		Vector3^ Position;
		Vector3^ Rotation;
		Vector3^ Scale;

		TransformComponent(Vector3^ position, Vector3^ rotation, Vector3^ scale)
		{
			this->Type = ComponentType::TransformComponent;
			this->Position = position;
			this->Rotation = rotation;
			this->Scale = scale;
		}
	};

}