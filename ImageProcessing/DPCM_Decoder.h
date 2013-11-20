#pragma once
#include "BitVector.h"
#include "ByteVecotr.h"

class DPCM_Decoder
{
private:
	int compress_data_length;
	byte placeHolder;

public:
	DPCM_Decoder(int len, byte ph);
	virtual ~DPCM_Decoder();

	ByteVecotrPtr transitData(BitVectorPtr src);
};

