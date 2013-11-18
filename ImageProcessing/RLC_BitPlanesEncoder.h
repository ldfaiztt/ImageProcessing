#pragma once
#include "BitVector.h"

class RLC_BitPlanesEncoder
{

public:
	RLC_BitPlanesEncoder();
	virtual ~RLC_BitPlanesEncoder();

	BitVectorPtr transitData(BitVectorPtr src);
};

