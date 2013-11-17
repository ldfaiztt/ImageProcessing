#include "stdafx.h"
#include "GeometricFilter.h"
#include "ImageMask.h"

GeometricFilter::GeometricFilter()
{
}


GeometricFilter::GeometricFilter(typeImgParaPtr imgP)
: MedianFilter(imgP)
{
}


GeometricFilter::~GeometricFilter()
{
}

byte GeometricFilter::Geometric(shared_ptr<ImageMask> src, int index)
{
	int srcW = src->GetWidth();
	int srcH = src->GetHeight();

	double prod = 1;
	for (int i = 0; i < srcH; i++)
	{
		for (int j = 0; j < srcW; j++)
		{
			prod *= src->getByteVal(j, i, index);
		}
	}

	return pow(prod, 1 / (double)(srcH * srcW));
}

byte GeometricFilter::ProcessingMask(shared_ptr<ImageMask> src, int index)
{
	return Geometric(src, index);
}
