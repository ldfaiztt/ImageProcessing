#include "stdafx.h"
#include "DPCM_Encoder.h"


DPCM_Encoder::DPCM_Encoder(int len)
	:compress_data_length(len)
{
}

DPCM_Encoder::~DPCM_Encoder()
{
}

BitVectorPtr DPCM_Encoder::transitData(ByteVecotrPtr src)
{
	BitVectorPtr ret(new BitVector());
	ret->clear();

	int max = pow(2, compress_data_length - 1) - 1;
	int min = -1 * pow(2, compress_data_length - 1);
	byte placeHolder = max;
	max--;

	byte predictor = 0;
	for (ByteVecotr::iterator it = src->begin(); it != src->end(); it++)
	{
		byte current = *it;
		int diff = current - predictor;
		if (diff > max || diff < min)
		{
			BitVector mark(compress_data_length, placeHolder);
			for (BitVector::size_type i = 0; i < mark.size(); i++)
			{
				ret->push_back(mark[i]);
			}

			BitVector oriVal(sizeof(byte)* 8, current);
			for (BitVector::size_type i = 0; i < oriVal.size(); i++)
			{
				ret->push_back(oriVal[i]);
			}
		}
		else
		{
			BitVector bits(compress_data_length, diff);
			for (BitVector::size_type i = 0; i < bits.size(); i++)
			{
				ret->push_back(bits[i]);
			}
		}
		predictor = current;
	}

	return ret;
}
