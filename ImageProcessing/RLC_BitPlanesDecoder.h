#pragma once
#include "BitVector.h"

class RLC_BitPlanesDecoder
{
public:
	RLC_BitPlanesDecoder();
	virtual ~RLC_BitPlanesDecoder();

	BitVectorPtr transitData(BitVectorPtr src);
};

