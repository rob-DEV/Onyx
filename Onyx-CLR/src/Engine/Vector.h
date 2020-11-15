#pragma once

//POD for passing to engine
public ref class Vector2
{
	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	float x, y;
};

public ref class Vector3
{
	Vector3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	float x, y, z;
};

