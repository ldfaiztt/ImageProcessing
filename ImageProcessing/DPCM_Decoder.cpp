#include "stdafx.h"
#include "DPCM_Decoder.h"


DPCM_Decoder::DPCM_Decoder(int len)
	:compress_data_length(len)
{
}


DPCM_Decoder::~DPCM_Decoder()
{
}

ByteVecotrPtr DPCM_Decoder::transitData(BitVectorPtr src)
{
	ByteVecotrPtr ret(new ByteVecotr());
	ret->clear();

	int max = pow(2, compress_data_length - 1) - 1;
	byte placeHolder = max;

	byte predictor = 0;
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
				current = diff + predictor;
			}
			else
			{
				bits.resize(compress_data_length - 1);
				bits.flip();
				current = ((bits.to_ulong() + 1) * -1) + predictor;
			}
		}

		ret->push_back(current);

		predictor = current;
	}

	return ret;
}
