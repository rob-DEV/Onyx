#pragma once

using namespace System;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;
using namespace System::Runtime::InteropServices;

public ref class DirectBitmap
{
public:
	System::Drawing::Bitmap^ Bitmap;
	array<System::Int32>^ Bits;
	bool Disposed;
	int Height;
	int Width;

	GCHandle BitsHandle;

	DirectBitmap(int width, int height)
	{
		Width = width;
		Height = height;
		Bits = gcnew array<System::Int32>(width * height);
		BitsHandle = GCHandle::Alloc(Bits, GCHandleType::Pinned);
		Bitmap = gcnew System::Drawing::Bitmap(width, height, width * 4, PixelFormat::Format32bppPArgb, BitsHandle.AddrOfPinnedObject());
	}

	void SetPixel(int x, int y, Color colour)
	{
		int index = x + (y * Width);
		int col = colour.ToArgb();

		Bits[index] = col;
	}

	void SetPixel(int index, Color colour)
	{
		int col = colour.ToArgb();
		Bits[index] = col;
	}

	Color GetPixel(int x, int y)
	{
		int index = x + (y * Width);
		int col = Bits[index];
		Color result = Color::FromArgb(col);

		return result;
	}

};

