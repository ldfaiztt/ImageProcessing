#include "stdafx.h"
#include "HistogramLocal.h"


HistogramLocal::HistogramLocal()
{
	mask_size = 3;
}

HistogramLocal::HistogramLocal(shared_ptr<stImgPara> imgP)
{
	if (imgP == NULL)
	{
		mask_size = 3;
	}
	else
	{
		mask_size = imgP->width;
	}
}


HistogramLocal::~HistogramLocal()
{
}

shared_ptr<CImage> HistogramLocal::transit(shared_ptr<CImage> src)
{
	int srcW = src->GetWidth();
	int srcH = src->GetHeight();

	shared_ptr<CImage> dst(new CImage());
	dst->Create(srcW, srcH, src->GetBPP());

	for (int i = 0; i < srcW; i++)
	{
		for (int j = 0; j < srcH; j++)
		{
			COLORREF pixel = src->GetPixel(i, j);
			int r = GetRValue(pixel);
		}
	}

	return dst;
}