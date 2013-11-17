#include "stdafx.h"
#include "MidPointFilter.h"
#include "ImageMask.h"
#include <vector>
#include <algorithm>

MidPointFilter::MidPointFilter()
{
}

MidPointFilter::MidPointFilter(typeImgParaPtr imgP)
: MedianFilter(imgP)
{
}

MidPointFilter::~MidPointFilter()
{
}

byte MidPointFilter::MidVectorSort(shared_ptr<ImageMask> src, int index)
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

	return (array[0] + array[array.size() - 1]) / 2;
}

byte MidPointFilter::ProcessingMask(shared_ptr<ImageMask> src, int index)
{
	return MidVectorSort(src, index);
}
