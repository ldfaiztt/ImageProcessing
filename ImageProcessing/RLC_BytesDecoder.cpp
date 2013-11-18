#include "stdafx.h"
#include "RLC_BytesDecoder.h"


RLC_BytesDecoder::RLC_BytesDecoder(int lineNum, byte placeHolder)
{
	LineNum = lineNum;
	PlaceHolder = placeHolder;
}

RLC_BytesDecoder::~RLC_BytesDecoder()
{
}

ByteVecotrPtr RLC_BytesDecoder::DecoderWithoutTag(ByteVecotrPtr src)
{
	ByteVecotrPtr ret = ByteVecotrPtr(new ByteVecotr());
	ret->clear();

	if (src->size() <= 0)
	{
		return ret;
	}

	for (ByteVecotr::iterator it = src->begin(); it != src->end();)
	{
		byte elem = *it++;
		byte count = *it++;

		for (int i = 0; i < count; i++)
		{
			ret->push_back(elem);
		}
	}

	return ret;
}

ByteVecotrPtr RLC_BytesDecoder::DecoderWithTag(ByteVecotrPtr src, byte PlaceHolder, int LineNum)
{
	ByteVecotrPtr ret = ByteVecotrPtr(new ByteVecotr());
	ret->clear();

	if (src->size() <= 0)
	{
		return ret;
	}

	for (ByteVecotr::iterator it = src->begin(); it != src->end();)
	{
		if (it == src->begin())
		{
			while (*it != PlaceHolder)
			{
				it++;
			}
			it++;
		}

		int countLine = 0;
		while (countLine < LineNum)
		{
			byte elem = *it++;
			if (elem == PlaceHolder)
			{
				break;
			}

			byte count = *it++;
			if (count == PlaceHolder)
			{
				break;
			}

			for (int i = 0; i < count; i++)
			{
				if (countLine >= LineNum)
				{
					break;
				}

				ret->push_back(elem);
				countLine++;
			}
		}

		if (countLine < LineNum)
		{
			for (int i = 0; i < LineNum - countLine; i++)
			{
				ret->push_back(*(it - 1));
			}
		}
		else
		{
			while (*it != PlaceHolder)
			{
				it++;
			}
			it++;
		}
	}

	return ret;
}

ByteVecotrPtr RLC_BytesDecoder::transitData(ByteVecotrPtr src)
{
	if (LineNum > 0)
	{
		return DecoderWithTag(src, PlaceHolder, LineNum);
	}
	else
	{
		return DecoderWithoutTag(src);
	}
}