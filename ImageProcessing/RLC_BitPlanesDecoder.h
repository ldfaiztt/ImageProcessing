#pragma once
#include "BitVector.h"
#include "ByteVecotr.h"

class RLC_BitPlanesDecoder
{
private:
	int line_num;
	bool predictor;
public:
	RLC_BitPlanesDecoder(int num, bool pred);
	virtual ~RLC_BitPlanesDecoder();

	BitVectorPtr transitData(ByteVecotrPtr src);
};

