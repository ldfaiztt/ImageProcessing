#include "stdafx.h"
#include "ContraharmonicFilter.h"
#include "ImageMask.h"

ContraharmonicFilter::ContraharmonicFilter()
{
	Q = 1;
}


ContraharmonicFilter::ContraharmonicFilter(typeImgParaPtr imgP)
: MedianFilter(imgP)
{
	Q = 1;
}

ContraharmonicFilter::~ContraharmonicFilter()
{
}

byte ContraharmonicFilter::Contraharmonic(shared_ptr<ImageMask> src, int index)
{
	int srcW = src->GetWidth();
	int srcH = src->GetHeight();

	int sum = 0;
	int sum_pow = 0;
	for (int i = 0; i < srcH; i++)
	{
		for (int j = 0; j < srcW; j++)
		{
			byte r = src->getByteVal(j, i, index);
			sum += pow(r, Q);
			sum_pow += pow(r, Q + 1);
		}
	}

	if (sum == 0)
	{
		return 0;
	}

	return sum_pow / sum;
}

byte ContraharmonicFilter::ProcessingMask(shared_ptr<ImageMask> src, int index)
{
	return Contraharmonic(src, index);
}
