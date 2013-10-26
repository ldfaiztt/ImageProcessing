#include "stdafx.h"
#include "Laplacian.h"
#include "ImageMask.h"


LaplacianFilter::LaplacianFilter()
{
	Init_laplacian_nag4();
}

LaplacianFilter::LaplacianFilter(typeImgParaPtr imgP)
{
	if (imgP == NULL)
	{
		Init_laplacian_nag4();
	}
	else
	{
		switch (imgP->mask_type)
		{
		case maskType::laplacian_nag4:
			Init_laplacian_nag4();
			break;

		case maskType::laplacian_nag8:
			Init_laplacian_nag8();
			break;

		case maskType::laplacian_pos4:
			Init_laplacian_pos4();
			break;

		case maskType::laplacian_pos8:
			Init_laplacian_pos8();
			break;

		default:
			Init_laplacian_nag4();
			break;
		}
	}
}

void LaplacianFilter::Init_laplacian_nag4()
{
	weight_mask[0][0] = 0;
	weight_mask[0][1] = 1;
	weight_mask[0][2] = 0;
	weight_mask[1][0] = 1;
	weight_mask[1][1] = -4;
	weight_mask[1][2] = 1;
	weight_mask[2][0] = 0;
	weight_mask[2][1] = 1;
	weight_mask[2][2] = 0;
}


void LaplacianFilter::Init_laplacian_nag8()
{
	weight_mask[0][0] = 1;
	weight_mask[0][1] = 1;
	weight_mask[0][2] = 1;
	weight_mask[1][0] = 1;
	weight_mask[1][1] = -8;
	weight_mask[1][2] = 1;
	weight_mask[2][0] = 1;
	weight_mask[2][1] = 1;
	weight_mask[2][2] = 1;
}

void LaplacianFilter::Init_laplacian_pos4()
{
	weight_mask[0][0] = 0;
	weight_mask[0][1] = -1;
	weight_mask[0][2] = 0;
	weight_mask[1][0] = -1;
	weight_mask[1][1] = 4;
	weight_mask[1][2] = -1;
	weight_mask[2][0] = 0;
	weight_mask[2][1] = -1;
	weight_mask[2][2] = 0;
}

void LaplacianFilter::Init_laplacian_pos8()
{
	weight_mask[0][0] = -1;
	weight_mask[0][1] = -1;
	weight_mask[0][2] = -1;
	weight_mask[1][0] = -1;
	weight_mask[1][1] = 8;
	weight_mask[1][2] = -1;
	weight_mask[2][0] = -1;
	weight_mask[2][1] = -1;
	weight_mask[2][2] = -1;
}

LaplacianFilter::~LaplacianFilter()
{
}

int LaplacianFilter::sharpening(shared_ptr<ImageMask> src, int index)
{
	int sum = 0;
	for (int i = 0; i < mask_size; i++)
	{
		for (int j = 0; j < mask_size; j++)
		{
			sum +=	src->getByteVal(i, j, index) * weight_mask[i][j];
		}
	}

	int mm_weight = weight_mask[mask_size / 2][mask_size / 2];

	int ret = 0;

	if (mm_weight > 0)
	{
		ret = src->getByteVal(mask_size / 2, mask_size / 2, index) + sum;
	} 
	else if (mm_weight < 0)
	{
		ret = src->getByteVal(mask_size / 2, mask_size / 2, index) - sum;
	}

	return ret;
}

typeImgPtr LaplacianFilter::transit(typeImgPtr src)
{
	int srcW = src->GetWidth();
	int srcH = src->GetHeight();

	typeImgPtr dst(new MyImage());
	dst->Create(srcW, srcH, src->GetBPP());
	ResetDstColorTable(src, dst);

	int dstW = dst->GetWidth();
	int dstH = dst->GetHeight();
	int dstClrCount = dst->GetBPP() / 8;

	byte * srcBuf = (byte *)src->GetBits();
	byte * dstBuf = (byte *)dst->GetBits();

	for (int i = 0; i < srcH; i++)
	{
		for (int j = 0; j < srcW; j++)
		{
			shared_ptr<ImageMask> mask(new ImageMask(*src, mask_size, j, i));
			for (int index = 0; index < dstClrCount; index++)
			{
				byte g = sharpening(mask,index);
				dst->setByteVal(j, i, index, g);
			}

		}
	}

	return dst;
}
