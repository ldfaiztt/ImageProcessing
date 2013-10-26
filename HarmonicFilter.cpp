#include "stdafx.h"
#include "HarmonicFilter.h"
#include "ImageMask.h"


HarmonicFilter::HarmonicFilter()
{
}


HarmonicFilter::HarmonicFilter(typeImgParaPtr imgP)
: MedianFilter(imgP)
{
}


HarmonicFilter::~HarmonicFilter()
{
}

byte HarmonicFilter::Harmonic(shared_ptr<ImageMask> src, int index)
{
	int srcW = src->GetWidth();
	int srcH = src->GetHeight();

	double sum = 0;
	for (int i = 0; i < srcH; i++)
	{
		for (int j = 0; j < srcW; j++)
		{
			sum += (1 / (double)src->getByteVal(j, i, index));
		}
	}

	return (srcH * srcW) / sum;
}

byte HarmonicFilter::ProcessingMask(shared_ptr<ImageMask> src, int index)
{
	return Harmonic(src, index);
}
