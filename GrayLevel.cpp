#include "stdafx.h"
#include "GrayLevel.h"

GrayLevel::GrayLevel()
{
	dstL = 8;
}

GrayLevel::GrayLevel(typeImgParaPtr imgP)
{
	if (imgP == NULL)
	{
		dstL = 8;
	}
	else
	{
		dstL = imgP->bit_size;
	}

}


GrayLevel::~GrayLevel()
{
}

int GrayLevel::mapGrayL(int src)
{
	float ratioL = pow(2, srcL) / pow(2, dstL);

	return (floor)(src / ratioL);
}

typeImgPtr GrayLevel::transit(typeImgPtr src)
{
	int srcW = src->GetWidth();
	int srcH = src->GetHeight();
	int srcRowBytes = src->GetPitch();
	srcL = src->GetBPP();

	typeImgPtr dst(new MyImage());
	dst->Create(srcW, srcH, dstL);
	ResetDstColorTable(src, dst);

	int dstW = dst->GetWidth();
	int dstH = dst->GetHeight();
	int dstRowBytes = dst->GetPitch();

	byte * srcBuf = (byte *)src->GetBits();
	byte * dstBuf = (byte *)dst->GetBits();

	for (int i = 0; i < dstH; i++)
	{
		for (int j = 0; j < dstW; j++)
		{
			byte r = srcBuf[i * srcRowBytes + j];
			byte g = mapGrayL(r);
			dstBuf[i * dstRowBytes + (j * dstL) / 8] |= (g << ((j * dstL) % 8));
		}
	}

	return dst;
}