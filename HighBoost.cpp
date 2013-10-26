#include "stdafx.h"
#include "HighBoost.h"
#include "ImageMask.h"

HighBoostFilter::HighBoostFilter()
	:LaplacianFilter()
{
	A = 1.7;
}

HighBoostFilter::HighBoostFilter(typeImgParaPtr imgP)
	: LaplacianFilter(imgP)
{
	if (imgP == NULL)
	{
		A = 1.7;
	}
	else
	{
		A = imgP->A;
	}
}

HighBoostFilter::~HighBoostFilter()
{
}

int HighBoostFilter::sharpening(shared_ptr<ImageMask> src, int index)
{
	int sum = 0;
	for (int i = 0; i < mask_size; i++)
	{
		for (int j = 0; j < mask_size; j++)
		{
			sum += src->getByteVal(i, j, index) * weight_mask[i][j];
		}
	}

	int mm_weight = weight_mask[mask_size / 2][mask_size / 2];

	int ret = 0;

	if (mm_weight > 0)
	{
		ret = (src->getByteVal(mask_size / 2, mask_size / 2, index) * A) + sum;
	}
	else if (mm_weight < 0)
	{
		ret = (src->getByteVal(mask_size / 2, mask_size / 2, index) * A) - sum;
	}

	return ret;
}