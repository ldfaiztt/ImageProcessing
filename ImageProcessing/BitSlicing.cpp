#include "stdafx.h"
#include "BitSlicing.h"


BitSlicingReConstruct::BitSlicingReConstruct()
	:BitSlicingSet()
{
	CountBitPlane(bit_mask);
}

BitSlicingReConstruct::BitSlicingReConstruct(typeImgParaPtr imgP)
	: BitSlicingSet(imgP)
{
	CountBitPlane(bit_mask);
}

int BitSlicingReConstruct::CountBitPlane(byte mask)
{
	for (int i = 0; i < 8; i++)
	{
		if ((mask & ByteMask[i]) > 0)
		{
			bit_planes.push_back(i);
		}
	}

	return bit_planes.size();
}

BitSlicingReConstruct::~BitSlicingReConstruct()
{
}

typeImgPtr BitSlicingReConstruct::transit(typeImgPtr src)
{
	int srcW = src->GetWidth();
	int srcH = src->GetHeight();
	int srcRowBytes = src->GetPitch();

	int dstL;
	if (bit_planes.size() == 1)
	{
		dstL = 1;
	}
	else if (bit_planes.size() <= 4)
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

	for (int i = 0; i < srcH; i++)
	{
		for (int j = 0; j < srcW; j++)
		{
			byte r = srcBuf[i * srcRowBytes + j];
			byte g = 0;
			for (int p = 0; p < bit_planes.size(); p++)
			{
				if ((r & ByteMask[bit_planes[p]]) > 0)
				{
					g |= (1 << p);
				}
			}

			dstBuf[i * dstRowBytes + (j * dstL) / 8] |= (g << ((j * dstL) % 8));
		}
	}

	return dst;
}
