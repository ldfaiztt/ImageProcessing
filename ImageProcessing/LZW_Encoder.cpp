#include "stdafx.h"
#include "LZW_Encoder.h"

LZW_Encoder::LZW_Encoder(int len)
	:compress_data_length(len)
{
	for (int i = 0; i <= 0xff; i++)
	{
		dictionary[string(1, i)] = i;
	}
}


LZW_Encoder::~LZW_Encoder()
{
}

BitVectorPtr LZW_Encoder::transitData(ByteVecotrPtr src)
{
	BitVectorPtr ret(new BitVector());
	ret->clear();

	lzwKey str = "";
	int testCount = 0;
	for (ByteVecotr::iterator it = src->begin(); it != src->end(); it++)
	{
		char curC = *it;

		if (dictionary.count(str + curC) > 0)
		{
			str += curC;
		}
		else  
		{
			BitVector bits(compress_data_length, dictionary[str]);
			for (BitVector::size_type i = 0; i < bits.size(); i++)
			{
				ret->push_back(bits[i]);
			}
			int tmp = bits.to_ulong();

			dictionary[str + curC] = dictionary.size();  
			str = curC;
		}

		testCount++;
	}

	if (!str.empty())
	{
		BitVector bits(compress_data_length, dictionary[str]);
		for (BitVector::size_type i = 0; i < bits.size(); i++)
		{
			ret->push_back(bits[i]);
		}
	}

	return ret;
}
