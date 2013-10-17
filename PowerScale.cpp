#include "stdafx.h"
#include "PowerScale.h"


PowerScale::PowerScale()
{
	c = 1.0;
	y = 1.0;
}

PowerScale::PowerScale(shared_ptr<stImgPara> imgP)
{
	if (imgP == NULL)
	{
		c = 1.0;
		y = 1.0;
	}
	else
	{
		c = imgP->c;
		y = imgP->y;
	}

}


PowerScale::~PowerScale()
{
}

int PowerScale::Pow(int inV)
{
	return (floor)(pow(inV, y) * c);
}

shared_ptr<CImage> PowerScale::transit(shared_ptr<CImage> src)
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
			int rr = GetRValue(pixel);
			int rg = GetGValue(pixel);
			int rb = GetBValue(pixel);

			int sr = Pow(rr);
			int sg = Pow(rg);
			int sb = Pow(rb);

			dst->SetPixelRGB(i, j, sr, sg, sb);
		}
	}

	return dst;
}