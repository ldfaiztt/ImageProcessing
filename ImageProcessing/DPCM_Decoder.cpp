#include "stdafx.h"
#include "DPCM_Decoder.h"


DPCM_Decoder::DPCM_Decoder(int len, byte ph)
	:compress_data_length(len),
	placeHolder(ph)
{
}


DPCM_Decoder::~DPCM_Decoder()
{
}

ByteVecotrPtr DPCM_Decoder::transitData(BitVectorPtr src)
{
	ByteVecotrPtr ret(new ByteVecotr());
	ret->clear();

	byte predictor;
	for (BitVector::size_type i = 0; i < src->size(); )
	{
		BitVector bits;
		for (BitVector::size_type j = 0; j < compress_data_length && i < src->size(); j++)
		{
			bits.push_back((*src)[i++]);
		}

		auto diff = bits.to_ulong();
		byte current = 0;
		if (diff == placeHolder)
		{
			bits.clear();
			for (BitVector::size_type k = 0; k < sizeof(byte) * 8 && i < src->size(); k++)
			{
				bits.push_back((*src)[i++]);
			}

			current = bits.to_ulong();
		}
		else
		{
			if (bits[compress_data_length - 1] == 0)
			{
				current = diff;
			}
			else
			{
				bits.resize(compress_data_length - 1);
				bits.flip();
				current = (bits.to_ulong() + 1) * -1;
			}
		}

		ret->push_back(current);
	}

	return ret;
}
