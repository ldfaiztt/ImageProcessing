#include "stdafx.h"
#include "BitSlicingSet.h"


BitSlicingSet::BitSlicingSet()
{
	bit_mask = 0xff;
}

BitSlicingSet::BitSlicingSet(typeImgParaPtr imgP)
{
	if (imgP == NULL)
	{
		bit_mask = 0xff;
	}
	else
	{
		bit_mask = imgP->bit_mask;
	}
}


BitSlicingSet::~BitSlicingSet()
{
}

typeImgPtr BitSlicingSet::transit(typeImgPtr src)
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

	byte * srcBuf = (byte *)src->GetBits();
	byte * dstBuf = (byte *)dst->GetBits();

	for (int i = 0; i < srcH; i++)
	{
		for (int j = 0; j < srcW; j++)
		{
			for (int index = 0; index < dstClrCount; index++)
			{
				byte g = srcBuf[i * srcRowBytes + j * srcClrCount + index] & bit_mask;
				dstBuf[i * dstRowBytes + j * dstClrCount + index] = g;
			}

		}
	}

	return dst;
}