#include "stdafx.h"
#include "RLC_BytesEncoder.h"

RLC_BytesEncoder::RLC_BytesEncoder(int lineNum, byte placeHolder)
	:TransData()
{
	LineNum = lineNum;
	PlaceHolder = placeHolder;
}

RLC_BytesEncoder::RLC_BytesEncoder(int lineNum, byte placeHolder, TransData * pre)
	: TransData(pre)
{
	LineNum = lineNum;
	PlaceHolder = placeHolder;
}


RLC_BytesEncoder::~RLC_BytesEncoder()
{
}

ByteVecotrPtr RLC_BytesEncoder::EncoderWithoutTag(ByteVecotrPtr src)
{
	ByteVecotrPtr ret = ByteVecotrPtr(new ByteVecotr());
	ret->clear();

	if (src->size() <= 0)
	{
		return ret;
	}

	byte prevElem = *(src->begin());
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
	}

	ret->push_back(prevElem);
	ret->push_back(elemCount);

	return ret;
}

ByteVecotrPtr RLC_BytesEncoder::EncoderWithTag(ByteVecotrPtr src, byte PlaceHolder, int LineNum)
{
	if (LineNum <= 0)
	{
		return EncoderWithoutTag(src);
	}

	ByteVecotrPtr ret = ByteVecotrPtr(new ByteVecotr());
	ret->clear();

	if (src->size() <= 0)
	{
		return ret;
	}

	byte prevElem = *(src->begin());
	ret->push_back(PlaceHolder);
	
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
		if (byteCount >= LineNum)
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

ByteVecotrPtr RLC_BytesEncoder::transitDataOwn(ByteVecotrPtr src)
{
	if (LineNum > 0)
	{
		return EncoderWithTag(src, PlaceHolder, LineNum);
	}
	else
	{
		return EncoderWithoutTag(src);
	}
}
