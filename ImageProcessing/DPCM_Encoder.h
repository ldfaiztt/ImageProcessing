#pragma once
#include "BitVector.h"
#include "ByteVecotr.h"

class DPCM_Encoder
{
private:
	int compress_data_length;
	byte placeHolder;

public:
	DPCM_Encoder(int len, byte ph);
	virtual ~DPCM_Encoder();

	BitVectorPtr transitData(ByteVecotrPtr src);
};

