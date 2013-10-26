#include "stdafx.h"
#include "MinFilter.h"
#include "ImageMask.h"
#include <algorithm>
#include <vector>

MinFilter::MinFilter()
{
}

MinFilter::MinFilter(typeImgParaPtr imgP)
: MedianFilter(imgP)
{
}

MinFilter::~MinFilter()
{
}

byte MinFilter::MinVectorSort(shared_ptr<ImageMask> src, int index)
{
	int srcW = src->GetWidth();
	int srcH = src->GetHeight();

	std::vector<byte> array;
	for (int i = 0; i < srcH; i++)
	{
		for (int j = 0; j < srcW; j++)
		{
			byte r = src->getByteVal(j, i, index);
			array.push_back(r);
		}
	}

	std::sort(array.begin(), array.end());

	return array[0];
}

byte MinFilter::ProcessingMask(shared_ptr<ImageMask> src, int index)
{
	return MinVectorSort(src, index);
}