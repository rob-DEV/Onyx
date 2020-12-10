#pragma once

namespace OnyxCLR {

	public ref class Vector2 {
	public:
		float X;
		float Y;

		Vector2(float x, float y)
		{
			this->X = x;
			this->Y = y;
		}

	};


	public ref class Vector3 {
	public:
		float X;
		float Y;
		float Z;

		Vector3(float x, float y, float z)
		{
			this->X = x;
			this->Y = y;
			this->Z = z;
		}

	};


	public ref class Vector4 {
	public:
		float X;
		float Y;
		float Z;
		float W;

		Vector4(float x, float y, float z, float w)
		{
			this->X = x;
			this->Y = y;
			this->Z = z;
			this->W = w;
		}
	};


}