#include "stdafx.h"
#include "nearest_neighbor.h"


NearestNeighbor::NearestNeighbor()
{
	dstW = 480;
	dstH = 640;
}

NearestNeighbor::NearestNeighbor(shared_ptr<stImgPara> imgP)
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

shared_ptr<CImage> NearestNeighbor::transit(shared_ptr<CImage> src)
{
	int srcW = src->GetWidth();
	int srcH = src->GetHeight();

	shared_ptr<CImage> dst(new CImage());
	dst->Create(dstW, dstH, src->GetBPP());

	int ratioX = ((srcW << 16) / dstW) + 1;
	int ratioH = ((srcH << 16) / dstH) + 1;

	//int * srcArr = (int *)src->GetBits();
	//int * dstArr = (int *)dst->GetBits();

	for (int i = 0; i < dstH; i++)
	{
		for (int j = 0; j < dstW; j++)
		{
			int dstX = (i * ratioX) >> 16;
			int dstY = (j * ratioH) >> 16;

			if (dstY >= srcW)
			{
				dstY = srcW - 1;
			}

			if (dstX >= srcH)
			{
				dstX = srcH - 1;
			}

			dst->SetPixel(j, i, src->GetPixel(dstY, dstX));
		}
	}

	return dst;
}