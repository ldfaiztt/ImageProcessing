#include "stdafx.h"
#include "RLC_BitPlanesEncoder.h"


RLC_BitPlanesEncoder::RLC_BitPlanesEncoder()
{
}

RLC_BitPlanesEncoder::~RLC_BitPlanesEncoder()
{
}

BitVectorPtr RLC_BitPlanesEncoder::transitData(BitVectorPtr src)
{
	BitVectorPtr ret = BitVectorPtr(new BitVector());
	ret->clear();

	if (src->size() <= 0)
	{
		return ret;
	}

	bool prevElem = ~((*src)[0]);
	int elemCount = 0;
	ret->push_back(prevElem);

	for (BitVector::size_type i = 0; i < src->size(); i++)
	{
		if ((*src)[i] == prevElem)
		{
			elemCount++;
		}
		else
		{
			ret->push_back(elemCount);
			prevElem = (*src)[i];
			elemCount = 1;
		}
	}

	ret->push_back(elemCount);

	return ret;
}
