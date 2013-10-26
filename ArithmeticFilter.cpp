#include "stdafx.h"
#include "ArithmeticFilter.h"
#include "ImageMask.h"


ArithmeticFilter::ArithmeticFilter()
{
}

ArithmeticFilter::ArithmeticFilter(typeImgParaPtr imgP)
: MedianFilter(imgP)
{
}


ArithmeticFilter::~ArithmeticFilter()
{
}

byte ArithmeticFilter::Arithmetic(shared_ptr<ImageMask> src, int index)
{
	int srcW = src->GetWidth();
	int srcH = src->GetHeight();

	int sum = 0;
	for (int i = 0; i < srcH; i++)
	{
		for (int j = 0; j < srcW; j++)
		{
			sum += src->getByteVal(j, i, index);			
		}
	}

	return sum / (srcH * srcW);
}

byte ArithmeticFilter::ProcessingMask(shared_ptr<ImageMask> src, int index)
{
	return Arithmetic(src, index);
}