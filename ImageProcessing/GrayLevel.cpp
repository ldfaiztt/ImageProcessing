#include "stdafx.h"
#include "GrayLevel.h"

GrayLevel::GrayLevel()
{
	dst_L = 8;
}

GrayLevel::GrayLevel(typeImgParaPtr imgP)
{
	if (imgP == NULL)
	{
		dst_L = 8;
	}
	else
	{
		dst_L = imgP->bit_size;
	}

}


GrayLevel::~GrayLevel()
{
}

int GrayLevel::mapGrayL(int src)
{
	float ratioL = pow(2, srcL) / pow(2, dst_L);

	return (floor)(src / ratioL);
}

typeImgPtr GrayLevel::transit(typeImgPtr src)
{
	int srcW = src->GetWidth();
	int srcH = src->GetHeight();
	int srcRowBytes = src->GetPitch();
	srcL = src->GetBPP();

	int dstL;
	if (dst_L == 1)
	{
		dstL = 1;
	}
	else if (dst_L <= 4)
	{
		dstL = 4;
	}
	else
	{
		dstL = 8;
	}

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