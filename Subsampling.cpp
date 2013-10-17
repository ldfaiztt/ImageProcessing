#include "stdafx.h"
#include "Subsampling.h"

Subsampling::Subsampling()
{
	dstW = 120;
	dstH = 160;
}

Subsampling::Subsampling(shared_ptr<stImgPara> imgP)
{
	if (imgP == NULL)
	{
		dstW = 120;
		dstH = 160;
	}
	else
	{
		dstW = imgP->width;
		dstH = imgP->height;
	}
}


Subsampling::~Subsampling()
{
}

shared_ptr<CImage> Subsampling::transit(shared_ptr<CImage> src) 
{

	int srcW = src->GetWidth();
	int srcH = src->GetHeight();

	shared_ptr<CImage> dst(new CImage());
	dst->Create(dstW, dstH, src->GetBPP());

	int gcdW = Gcd(dstW, srcW);
	int gcdH = Gcd(dstH, srcH);

	int dstW_G = dstW / gcdW;
	int dstH_G = dstH / gcdH;
	int srcW_G = srcW / gcdW;
	int srcH_G = srcH / gcdH;

	for (int i = 0; i < dstW; i++)
	{
		for (int j = 0; j < dstH; j++)
		{
			dst->SetPixel(i, j, src->GetPixel(i*srcW_G / dstW_G, j*srcH_G / dstH_G));
		}
	}

	return dst;
}
