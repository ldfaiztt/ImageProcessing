#include "stdafx.h"
#include "nearest_neighbor.h"


NearestNeighbor::NearestNeighbor()
{
	dstW = 480;
	dstH = 640;
}

NearestNeighbor::NearestNeighbor(typeImgParaPtr imgP)
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


NearestNeighbor::~NearestNeighbor()
{
}

typeImgPtr NearestNeighbor::transit(typeImgPtr src)
{
	int srcW = src->GetWidth();
	int srcH = src->GetHeight();
	
	typeImgPtr dst(new MyImage());
	dst->Create(dstW, dstH, src->GetBPP());
	ResetDstColorTable(src, dst);

	int ratioX = ((srcW << 16) / dstW) + 1;
	int ratioH = ((srcH << 16) / dstH) + 1;

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
				int srcX = (i * ratioX) >> 16;
				int srcY = (j * ratioH) >> 16;

				if (srcY >= srcW)
				{
					srcY = srcW - 1;
				}

				if (srcX >= srcH)
				{
					srcX = srcH - 1;
				}

				byte g = srcBuf[srcX * srcRowBytes + srcY * srcClrCount + index];
				dstBuf[i * dstRowBytes + j * dstClrCount + index] = g;
			}
		}
	}

	return dst;
}