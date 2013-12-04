#include "stdafx.h"
#include "BitPlaneBuilder.h"


BitPlaneBuilder::BitPlaneBuilder()
{
}


BitPlaneBuilder::~BitPlaneBuilder()
{
}

int BitPlaneBuilder::build(typeImgPtr src, vector<BitVectorPtr> & result)
{
	build(src->toByteVector(), result);

	int width = src->GetWidth();
	int BytesPerPixel = (src->GetBPP() + 7) / 8;
	int LineNum = width * BytesPerPixel;

	return LineNum;
}

int BitPlaneBuilder::build(ByteVecotrPtr src, vector<BitVectorPtr> & result)
{
	
	for (int bit = 0; bit < 8; bit++)
	{
		byte bit_mask = 1 << bit;
		BitVectorPtr bits(new BitVector());

		for (ByteVecotr::iterator it = src->begin(); it != src->end(); it++)
		{
			if (*it & bit_mask > 0)
			{
				bits->push_back(true);
			}
			else
			{
				bits->push_back(false);
			}
		}

		result.push_back(bits);
	}

	return src->size();
}