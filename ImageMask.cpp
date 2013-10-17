#include "stdafx.h"
#include "ImageMask.h"

CImageMask::CImageMask(CImage & img, int size, coordinate x, coordinate y)
	:ori_img(img)
{
	mask_size = size;
	median_x = x;
	median_y = y;
}

CImageMask::~CImageMask()
{
}

coordinate CImageMask::route(coordinate src) const throw()
{
	if (mask_size > 0)
	{
		src = src % mask_size;
	}

	return src - (mask_size / 2);
}

int CImageMask::GetHeight() const throw()
{
	return mask_size;
}

int CImageMask::GetWidth() const throw()
{
	return mask_size;
}

COLORREF CImageMask::GetPixel(int x, int y) const throw()
{
	int dstX = median_x + route(x);
	int dstY = median_y + route(y);

	return ori_img.GetPixel(dstX,dstY);
}

void CImageMask::SetPixel(int x, int y, COLORREF color) throw()
{
	int dstX = median_x + route(x);
	int dstY = median_y + route(y);

	ori_img.SetPixel(dstX, dstY, color);
}

void CImageMask::SetPixelRGB(int x, int y, BYTE r, BYTE g, BYTE b) throw()
{
	int dstX = median_x + route(x);
	int dstY = median_y + route(y);

	ori_img.SetPixelRGB(dstX, dstY, r, g, b);
}