#include "stdafx.h"
#include "Smoothing.h"
#include "ImageMask.h"

Smoothing::Smoothing()
{
	DefaultInit();
}

Smoothing::Smoothing(typeImgParaPtr imgP)
{
	if (imgP == NULL)
	{
		DefaultInit();
	}
	else
	{
		mask_size = imgP->mask_size;
		if (mask_size == 3 && imgP->mask_type == maskType::average_1_16)
		{
			DefaultInit();
		}
		else
		{
			for (int i = 0; i < mask_size; i++)
			{
				vector<int> line;
				for (int j = 0; j < mask_size; j++)
				{
					line.push_back(1);
				}
				weight_mask.push_back(line);
			}
		}
	}
}

void Smoothing::DefaultInit()
{
	mask_size = 3;

	vector<int> line;

	line.push_back(1);
	line.push_back(2);
	line.push_back(1);
	weight_mask.push_back(line);

	line.clear();
	line.push_back(2);
	line.push_back(4);
	line.push_back(2);
	weight_mask.push_back(line);

	line.clear();
	line.push_back(1);
	line.push_back(2);
	line.push_back(1);
	weight_mask.push_back(line);
}

Smoothing::~Smoothing()
{
}

byte Smoothing::Average(shared_ptr<ImageMask> src, int index)
{
	int srcW = src->GetWidth();
	int srcH = src->GetHeight();

	int sum = 0;
	int weight = 0;
	for (int i = 0; i < srcH; i++)
	{
		for (int j = 0; j < srcW; j++)
		{
			byte r = src->getByteVal(j, i, index) * weight_mask[i][j];
			sum += r;
			weight += weight_mask[i][j];
		}
	}

	return floor(sum / weight);
}

typeImgPtr Smoothing::transit(typeImgPtr src)
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
				byte g = Average(mask, index);
				dst->setByteVal(j, i, index, g);
			}

		}
	}

	return dst;
}
