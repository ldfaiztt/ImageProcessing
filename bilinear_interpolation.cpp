#include "stdafx.h"
#include "bilinear_interpolation.h"

BilinearInterpolation::BilinearInterpolation()
{
	dstW = 480;
	dstH = 640;
}

BilinearInterpolation::BilinearInterpolation(shared_ptr<stImgPara> imgP)
{
	if (imgP == NULL)
	{
		dstW = 480;
		dstH = 640;
	}
	else
	{
		dstW = imgP->width;
		dstH = imgP->height;
	}
}


BilinearInterpolation::~BilinearInterpolation()
{
}

shared_ptr<CImage> BilinearInterpolation::transit(shared_ptr<CImage> src)
{
	int dstW = 480;
	int dstH = 640;

	int srcW = src->GetWidth();
	int srcH = src->GetHeight();

	shared_ptr<CImage> dst(new CImage());
	dst->Create(dstW, dstH, src->GetBPP());

	int A, B, C, D, x, y, index;

	float ratioX = ((float)(srcW - 1)) / dstW;
	float ratioY = ((float)(srcH - 1)) / dstH;

	for (int i = 0; i < dstH; i++)
	{
		for (int j = 0; j < dstW; j++)
		{
			x = (int)(ratioX * j);
			y = (int)(ratioY * i);
			float x_diff = (ratioX * j) - x;
			float y_diff = (ratioY * i) - y;
			index = y*srcW + x;

			COLORREF pixels_r = src->GetPixel(x, y);
			COLORREF pixels_c = src->GetPixel(x, y + 1);

		}
	}

	return dst;
}