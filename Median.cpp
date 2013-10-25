#include "stdafx.h"
#include "Median.h"
#include "ImageMask.h"
#include <list>
#include <vector>
#include <algorithm>
#include <iostream>

Median::Median()
{
	mask_size = 3;
}

Median::Median(typeImgParaPtr imgP)
{
	if (imgP == NULL)
	{
		mask_size = 3;
	}
	else
	{
		mask_size = imgP->mask_size;
	}
}

Median::~Median()
{
}

byte Median::MedianListSort(shared_ptr<ImageMask> src, int index)
{
	int srcW = src->GetWidth();
	int srcH = src->GetHeight();

	std::list<byte> list;
	for (int i = 0; i < srcH; i++)
	{
		for (int j = 0; j < srcW; j++)
		{
			byte r = src->getByteVal(j, i, index);
			list.push_back(r);
		}
	}
	list.sort();
	
	std::list<byte>::iterator it = std::next(list.begin(), list.size() / 2);

	return *it;
}

byte Median::MedianVectorSort(shared_ptr<ImageMask> src, int index)
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

	return array[array.size() / 2];
}

byte Median::MedianList(shared_ptr<ImageMask> src, int index)
{
	int srcW = src->GetWidth();
	int srcH = src->GetHeight();

	std::list<byte> list;
	for (int i = 0; i < srcH; i++)
	{
		for (int j = 0; j < srcW; j++)
		{
			byte r = src->getByteVal(j, i, index);
			std::list<byte>::iterator it = list.begin();
			for (; it != list.end(); it++)
			{
				if (r < *it)
				{
					it = list.insert(it, r);
					break;
				}
			}

			if (it == list.end())
			{
				list.push_back(r);
			}
		}
	}

	std::list<byte>::iterator it = std::next(list.begin(), list.size() / 2);

	return *it;
}

byte Median::MedianVector(shared_ptr<ImageMask> src, int index)
{
	int srcW = src->GetWidth();
	int srcH = src->GetHeight();

	std::vector<byte> array;
	for (int i = 0; i < srcH; i++)
	{
		for (int j = 0; j < srcW; j++)
		{
			byte r = src->getByteVal(j, i, index);
			std::vector<byte>::iterator it = array.begin();
			for (; it != array.end(); it++)
			{
				if (r < *it)
				{
					it = array.insert(it, r);
					break;
				}
			}

			if (it == array.end())
			{
				array.push_back(r);
			}
		}
	}

	return array[array.size() / 2];
}

typeImgPtr Median::transit(typeImgPtr src)
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
				byte g = MedianVectorSort(mask, index);
				dst->setByteVal(j, i, index, g);
			}

		}
	}

	return dst;
}
