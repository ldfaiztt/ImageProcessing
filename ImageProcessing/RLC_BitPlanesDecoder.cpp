#include "stdafx.h"
#include "RLC_BitPlanesDecoder.h"


RLC_BitPlanesDecoder::RLC_BitPlanesDecoder()
	:TransData()
{
}

RLC_BitPlanesDecoder::RLC_BitPlanesDecoder(TransData * pre)
	: TransData(pre)
{

}

RLC_BitPlanesDecoder::~RLC_BitPlanesDecoder()
{
}

BitVectorPtr RLC_BitPlanesDecoder::transitDataOwn(BitVectorPtr src)
{
	BitVectorPtr ret = BitVectorPtr(new BitVector());
	ret->clear();

	return ret;
}
