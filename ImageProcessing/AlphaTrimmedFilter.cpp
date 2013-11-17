#include "stdafx.h"
#include "AlphaTrimmedFilter.h"
#include "ImageMask.h"
#include <vector>
#include <algorithm>


AlphaTrimmedFilter::AlphaTrimmedFilter()
{
	N = 1;
}


AlphaTrimmedFilter::AlphaTrimmedFilter(typeImgParaPtr imgP)
: MedianFilter(imgP)
{
	N = 1;
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

	for (int i = 0; i < N; i++)
	{
		sum = sum - array[(array.size() - 1 - i) % array.size()] - array[(0 + i) % array.size()];
	}

	return sum / (array.size() - 2*N);
}

byte AlphaTrimmedFilter::ProcessingMask(shared_ptr<ImageMask> src, int index)
{
	return AlphaTrimmed(src, index);
}
