#include "stdafx.h"
#include "LogScale.h"


LogScale::LogScale()
{
	c = 20.0;
	//y = 1.0;
}

LogScale::LogScale(shared_ptr<stImgPara> imgP)
{
	if (imgP == NULL)
	{
		c = 20.0;
		//y = 1.0;
	}
	else
	{
		c = imgP->c;
		//y = imgP->y;
	}

}


LogScale::~LogScale()
{
}

int LogScale::Log(int inV)
{
	return (floor)(log(1 + inV) * c);
}

shared_ptr<CImage> LogScale::transit(shared_ptr<CImage> src)
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

			int sr = Log(rr);
			int sg = Log(rg);
			int sb = Log(rb);

			dst->SetPixelRGB(i, j, sr, sg, sb);
		}
	}

	return dst;
}
