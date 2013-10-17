#include "stdafx.h"
#include "GrayLevel.h"

GrayLevel::GrayLevel()
{
	dstL = 4;
}

GrayLevel::GrayLevel(shared_ptr<stImgPara> imgP)
{
	if (imgP == NULL)
	{
		dstL = 4;
	}
	else
	{
		dstL = imgP->height;
	}

}


GrayLevel::~GrayLevel()
{
}

int GrayLevel::mapGrayL(int src)
{
	float ratioL = pow(2,8) / pow(2,dstL);

	return (floor)(src / ratioL);
}

shared_ptr<CImage> GrayLevel::transit(shared_ptr<CImage> src)
{
	int srcW = src->GetWidth();
	int srcH = src->GetHeight();

	shared_ptr<CImage> dst(new CImage());

	srcL = src->GetBPP();
	dst->Create(srcW, srcH, src->GetBPP());

	for (int i = 0; i < srcW; i++)
	{
		for (int j = 0; j < srcH; j++)
		{
			COLORREF pixel = src->GetPixel(i, j);
			byte r = mapGrayL(GetRValue(pixel));
			byte g = mapGrayL(GetGValue(pixel));
			byte b = mapGrayL(GetBValue(pixel));

			dst->SetPixelRGB(i, j, r, g, b);
		}
	}

	return dst;
}