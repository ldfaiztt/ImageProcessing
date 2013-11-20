#pragma once
#include "BitVector.h"
#include "ByteVecotr.h"

class RLC_BitPlanesEncoder
{
private:
	int line_num;
	bool predictor;

public:
	RLC_BitPlanesEncoder(int num, bool pred);
	virtual ~RLC_BitPlanesEncoder();

	ByteVecotrPtr transitData(BitVectorPtr src);
};

