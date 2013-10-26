#include "stdafx.h"
#include "MaxFilter.h"
#include <vector>
#include <algorithm>
#include "ImageMask.h"

MaxFilter::MaxFilter()
	:MedianFilter()
{
}

MaxFilter::MaxFilter(typeImgParaPtr imgP)
: MedianFilter(imgP)
{
}

MaxFilter::~MaxFilter()
{
}

byte MaxFilter::MaxVectorSort(shared_ptr<ImageMask> src, int index)
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

	return array[array.size() - 1];
}

byte MaxFilter::ProcessingMask(shared_ptr<ImageMask> src, int index)
{
	return MaxVectorSort(src, index);
}