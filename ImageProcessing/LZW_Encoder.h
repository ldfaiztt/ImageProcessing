#pragma once
#include "ByteVecotr.h"
#include "BitVector.h"
#include <unordered_map>

class LZW_Encoder
{
typedef string lzwKey;
typedef int lzwVal;

private:
	unordered_map<lzwKey, lzwVal> dictionary;
	int compress_data_length;

public:
	LZW_Encoder(int len);
	virtual ~LZW_Encoder();

	BitVectorPtr transitData(ByteVecotrPtr src);
};

