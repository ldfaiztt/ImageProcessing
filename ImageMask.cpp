#include "stdafx.h"
#include "ImageMask.h"

ImageMask::ImageMask(MyImage & img, int size, coordinate x, coordinate y)
	:ori_img(img)
{
	mask_size = size;
	median_x = x;
	median_y = y;
}

ImageMask::~ImageMask()
{
}

coordinate ImageMask::route(coordinate src) const throw()
{
	if (mask_size > 0)
	{
		src = src % mask_size;
	}

	return src - (mask_size / 2);
}

int ImageMask::GetHeight() const throw()
{
	return mask_size;
}

int ImageMask::GetWidth() const throw()
{
	return mask_size;
}

int ImageMask::GetBPP() const
{
	return ori_img.GetBPP();
}

COLORREF ImageMask::GetPixel(int x, int y) const throw()
{
	int dstX = median_x + route(x);
	int dstY = median_y + route(y);

	if (dstX < 0)
	{
		dstX = 0;
	}

	if (dstX >= ori_img.GetWidth())
	{
		dstX = ori_img.GetWidth() - 1;
	}

	if (dstY < 0)
	{
		dstY = 0;
	}

	if (dstY >= ori_img.GetHeight())
	{
		dstY = ori_img.GetHeight() - 1;
	}

	return ori_img.GetPixel(dstX,dstY);
}

byte ImageMask::getByteVal(int x, int y, int index)
{
	int dstX = median_x + route(x);
	int dstY = median_y + route(y);

	if (dstX < 0)
	{
		dstX = 0;
	}

	if (dstX >= ori_img.GetWidth())
	{
		dstX = ori_img.GetWidth() - 1;
	}

	if (dstY < 0)
	{
		dstY = 0;
	}

	if (dstY >= ori_img.GetHeight())
	{
		dstY = ori_img.GetHeight() - 1;
	}

	return ori_img.getByteVal(dstX, dstY, index);
}

void ImageMask::SetPixel(int x, int y, COLORREF color) throw()
{
	int dstX = median_x + route(x);
	int dstY = median_y + route(y);

	if (dstX < 0 || dstX >= ori_img.GetWidth() || dstY < 0 || dstY >= ori_img.GetHeight())
	{
		return;
	}

	ori_img.SetPixel(dstX, dstY, color);
}

void ImageMask::SetPixelRGB(int x, int y, BYTE r, BYTE g, BYTE b) throw()
{
	int dstX = median_x + route(x);
	int dstY = median_y + route(y);

	if (dstX < 0 || dstX >= ori_img.GetWidth() || dstY < 0 || dstY >= ori_img.GetHeight())
	{
		return;
	}

	ori_img.SetPixelRGB(dstX, dstY, r, g, b);
}