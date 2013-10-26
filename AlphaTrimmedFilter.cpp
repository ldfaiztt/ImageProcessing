#include "stdafx.h"
#include "AlphaTrimmedFilter.h"
#include "ImageMask.h"
#include <vector>
#include <algorithm>


AlphaTrimmedFilter::AlphaTrimmedFilter()
{
}


AlphaTrimmedFilter::AlphaTrimmedFilter(typeImgParaPtr imgP)
: MedianFilter(imgP)
{
}

AlphaTrimmedFilter::~AlphaTrimmedFilter()
{
}

byte AlphaTrimmedFilter::AlphaTrimmed(shared_ptr<ImageMask> src, int index)
{
	int srcW = src->GetWidth();
	int srcH = src->GetHeight();

	std::vector<byte> array;
	int sum = 0;
	for (int i = 0; i < srcH; i++)
	{
		for (int j = 0; j < srcW; j++)
		{
			byte r = src->getByteVal(j, i, index);
			sum += r;
			array.push_back(r);
		}
	}

	std::sort(array.begin(), array.end());

	return (sum - array[array.size() - 1] - array[0]) / (array.size() - 2);
}

byte AlphaTrimmedFilter::ProcessingMask(shared_ptr<ImageMask> src, int index)
{
	return AlphaTrimmed(src, index);
}
