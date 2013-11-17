#include "stdafx.h"
#include "MyImage.h"


MyImage::MyImage()
{
}

MyImage::~MyImage()
{
}

byte MyImage::getByteVal(int x, int y, int index)
{
	return ((byte *)GetBits())[y * GetPitch() + x * (GetBPP() / 8) + index];
}

void MyImage::setByteVal(int x, int y, int index, byte val)
{
	((byte *)GetBits())[y * GetPitch() + x * (GetBPP() / 8) + index] = val;
}

COLORREF MyImage::GetPixel(_In_ int x, _In_ int y) const throw()
{
	return CImage::GetPixel(x, y);
}

void MyImage::SetPixel(int x, int y, COLORREF color) throw()
{
	return CImage::SetPixel(x, y, color);
}

void MyImage::SetPixelRGB(int x, int y, BYTE r, BYTE g, BYTE b) throw()
{
	return CImage::SetPixelRGB(x, y, r, g, b);
}

int MyImage::GetBPP() const
{
	return CImage::GetBPP();
}

int MyImage::GetWidth() const throw()
{
	return CImage::GetWidth();
}

int MyImage::GetHeight() const throw()
{
	return CImage::GetHeight();
}

ByteVecotrPtr MyImage::toByteVector()
{
	byte * data = (byte *)GetBits();
	byte * start = NULL;
	byte * end = NULL;

	int width = GetWidth();
	int height = GetHeight();
	int srcClrCount = GetBPP() / 8;
	int bytesPerLine = GetPitch();

	if (bytesPerLine > 0)
	{
		start = data;
		end = data + height * bytesPerLine;
	}
	else
	{
		start = data + (height - 1) * bytesPerLine;
		end = data + (bytesPerLine * (-1));
	}
	
	return ByteVecotrPtr(new ByteVecotr(start, end));
}