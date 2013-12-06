#include "stdafx.h"
#include "RLC_BitPlanesDecoder.h"


RLC_BitPlanesDecoder::RLC_BitPlanesDecoder(int num, bool pred)
	:line_num(num),
	predictor(pred)
{
}

RLC_BitPlanesDecoder::~RLC_BitPlanesDecoder()
{
}

BitVectorPtr RLC_BitPlanesDecoder::transitData(ByteVecotrPtr src)
{
	BitVectorPtr ret = BitVectorPtr(new BitVector());
	ret->clear();

	for (ByteVecotr::iterator it = src->begin(); it != src->end();)
	{
		bool pred = predictor;
		int lineCount = 0;

		while (lineCount < line_num && it != src->end())
		{
			byte elemCount = *it++;
			for (int i = 0; i < elemCount && lineCount < line_num; i++)
			{
				ret->push_back(pred);
				lineCount++;
			}
			pred = !pred;
		}
	}

	return ret;
}
