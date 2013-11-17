#include "stdafx.h"
#include "PowerScale.h"


PowerScaleFilter::PowerScaleFilter()
{
	c = 1.0;
	y = 1.0;
}

PowerScaleFilter::PowerScaleFilter(typeImgParaPtr imgP)
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


PowerScaleFilter::~PowerScaleFilter()
{
}

int PowerScaleFilter::Pow(int inV)
{
	return (floor)(pow(inV, y) * c);
}

typeImgPtr PowerScaleFilter::transit(typeImgPtr src)
{
	int srcW = src->GetWidth();
	int srcH = src->GetHeight();
	int srcRowBytes = src->GetPitch();
	int srcClrCount = src->GetBPP() / 8;

	typeImgPtr dst(new MyImage());
	dst->Create(srcW, srcH, src->GetBPP());
	ResetDstColorTable(src, dst);

	int dstW = dst->GetWidth();
	int dstH = dst->GetHeight();
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
				byte r = srcBuf[i * srcRowBytes + j * srcClrCount + index];
				dstBuf[i * dstRowBytes + j * dstClrCount + index] = Pow(r);
			}
		}
	}

	return dst;
}