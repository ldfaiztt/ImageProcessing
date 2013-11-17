#include "stdafx.h"
#include "Replication.h"


Replication::Replication()
{
	dstW = 480;
	dstH = 640;
}

Replication::Replication(typeImgParaPtr imgP)
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

typeImgPtr Replication::transit(typeImgPtr src) 
{
	int srcW = src->GetWidth();
	int srcH = src->GetHeight();

	typeImgPtr dst(new MyImage());
	dst->Create(dstW, dstH, src->GetBPP());
	ResetDstColorTable(src, dst);

	int gcdW = Gcd(dstW, srcW);
	int gcdH = Gcd(dstH, srcH);

	int dstW_G = dstW / gcdW;
	int dstH_G = dstH / gcdH;
	int srcW_G = srcW / gcdW;
	int srcH_G = srcH / gcdH;

	int srcRowBytes = src->GetPitch();
	int srcClrCount = src->GetBPP() / 8;
	int dstRowBytes = dst->GetPitch();
	int dstClrCount = dst->GetBPP() / 8;

	for (int index = 0; index < dstClrCount; index++)
	{
		byte * srcBuf = (byte *)src->GetBits();
		byte * dstBuf = (byte *)dst->GetBits();

		for (int i = 0; i < dstH; i++)
		{
			for (int j = 0; j < dstW; j++)
			{
				byte g = srcBuf[(i / (dstH_G / srcH_G)) * srcRowBytes + (j / (dstW_G / srcW_G)) * srcClrCount + index];
				dstBuf[i * dstRowBytes + j * dstClrCount + index] = g;
			}
		}
	}

	return dst;
}
