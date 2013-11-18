#pragma once

#include "ByteVecotr.h"
#include "BitVector.h"
#include <unordered_map>

typedef int lzwKey;
typedef string lzwVal;

class LZW_Decoder
{
private:
	unordered_map<lzwKey, lzwVal> dictionary;
	int compress_data_length;

public:
	LZW_Decoder(int len);
	virtual ~LZW_Decoder();

	ByteVecotrPtr transitData(BitVectorPtr src);
};

