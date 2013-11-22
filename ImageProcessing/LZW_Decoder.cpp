#include "stdafx.h"
#include "LZW_Decoder.h"


LZW_Decoder::LZW_Decoder(int len)
	:compress_data_length(len)
{
	for (int i = 0; i <= 0xff; i++)
	{
		dictionary[i] = string(1, i);
	}
}


LZW_Decoder::~LZW_Decoder()
{
}

ByteVecotrPtr LZW_Decoder::transitData(BitVectorPtr src)
{
	ByteVecotrPtr ret(new ByteVecotr());
	ret->clear();

	lzwVal entry = "";
	lzwVal oldCode = "";

	size_t index = dictionary.size() - 1;
	for (BitVector::size_type i = 0; i < src->size();)
	{
		BitVector bits;
		for (BitVector::size_type j = 0; j < compress_data_length && i < src->size(); j++)
		{
			bits.push_back((*src)[i++]);
		}
		
		auto key = bits.to_ulong();
		if (dictionary.count(key) > 0)
		{
			entry = dictionary[key];
		} 
		else if (key == dictionary.size())
		{
			entry = oldCode + oldCode[0];
		}
		else
		{
			throw "Bad compression code";
		}

		for (lzwVal::iterator it = entry.begin(); it != entry.end(); it++)
		{
			ret->push_back(*it);
		}

		dictionary[index++] = oldCode + entry[0];
		oldCode = entry;
	}

	return ret;
}
