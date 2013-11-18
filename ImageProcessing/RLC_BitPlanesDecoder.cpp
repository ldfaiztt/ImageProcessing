#include "stdafx.h"
#include "RLC_BitPlanesDecoder.h"


RLC_BitPlanesDecoder::RLC_BitPlanesDecoder()
{
}

RLC_BitPlanesDecoder::~RLC_BitPlanesDecoder()
{
}

BitVectorPtr RLC_BitPlanesDecoder::transitData(BitVectorPtr src)
{
	BitVectorPtr ret = BitVectorPtr(new BitVector());
	ret->clear();

	return ret;
}
