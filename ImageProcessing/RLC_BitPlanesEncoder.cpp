#include "stdafx.h"
#include "RLC_BitPlanesEncoder.h"


RLC_BitPlanesEncoder::RLC_BitPlanesEncoder(int num, bool pred)
	:line_num(num),
	predictor(pred)
{
}

RLC_BitPlanesEncoder::~RLC_BitPlanesEncoder()
{
}

ByteVecotrPtr RLC_BitPlanesEncoder::transitData(BitVectorPtr src)
{
	ByteVecotrPtr ret = ByteVecotrPtr(new ByteVecotr());
	ret->clear();

	if (src->size() <= 0)
	{
		return ret;
	}

	for (BitVector::size_type i = 0; i < src->size();)
	{
		bool pred = predictor;
		int elemCount = 0;

		for (int j = 0; j < line_num && i < src->size(); j++)
		{
			if ((*src)[i++] == pred)
			{
				elemCount++;
			}
			else
			{
				ret->push_back(elemCount);
				pred = !pred;
				elemCount = 1;
			}
		}

		if (elemCount > 0)
		{
			ret->push_back(elemCount);
		}
	}

	return ret;
}
