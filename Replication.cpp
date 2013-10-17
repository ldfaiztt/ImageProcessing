#include "stdafx.h"
#include "Replication.h"


Replication::Replication()
{
	dstW = 480;
	dstH = 640;
}

Replication::Replication(shared_ptr<stImgPara> imgP)
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


Replication::~Replication()
{
}

shared_ptr<CImage> Replication::transit(shared_ptr<CImage> src) 
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
			dst->SetPixel(i, j, src->GetPixel(i / (dstW_G / srcW_G), j / (dstH_G / srcH_G)));
		}
	}

	return dst;
}
