#include "stdafx.h"
#include "RLC_GrayScaleEncoder.h"

RLC_GrayScaleEncoder::RLC_GrayScaleEncoder(typeImgPtr img)
	:TransData()
{
	image = img;
}

RLC_GrayScaleEncoder::RLC_GrayScaleEncoder(typeImgPtr img, TransData * pre)
	: TransData(pre)
{
	image = img;
}


RLC_GrayScaleEncoder::~RLC_GrayScaleEncoder()
{
}

ByteVecotrPtr RLC_GrayScaleEncoder::transitDataOwn(ByteVecotrPtr src)
{
	ByteVecotrPtr ret = ByteVecotrPtr(new ByteVecotr());
	ret->clear();

	if (src->size() <= 0)
	{
		return ret;
	}

	int srcRowBytes = 0;
	if (image != NULL)
	{
		srcRowBytes = image->GetPitch();
	}

	byte prevElem = *(src->begin());
	if (srcRowBytes > 0)
	{
		ret->push_back(PlaceHolder);
	}
	int byteCount = 0;
	int elemCount = 0;

	for (ByteVecotr::iterator it = src->begin(); it != src->end(); it++)
	{
		if (*it == prevElem)
		{
			elemCount++;
		} 
		else
		{
			ret->push_back(prevElem);
			ret->push_back(elemCount);
			prevElem = *it;
			elemCount = 1;
		}

		byteCount++;
		if (srcRowBytes > 0 && byteCount >= srcRowBytes)
		{
			ret->push_back(prevElem);
			ret->push_back(elemCount);

			ret->push_back(PlaceHolder);

			byteCount = 0;
			elemCount = 0;

			ByteVecotr::iterator next = it + 1;
			if (next != src->end())
			{
				prevElem = *next;
			}
		}

	}

	return ret;
}
