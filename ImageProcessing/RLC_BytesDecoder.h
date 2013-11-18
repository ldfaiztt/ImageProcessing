#pragma once
#include "MyImage.h"

class RLC_BytesDecoder
{
private:
	byte PlaceHolder;
	int LineNum;

	ByteVecotrPtr DecoderWithoutTag(ByteVecotrPtr src);
	ByteVecotrPtr DecoderWithTag(ByteVecotrPtr src, byte PlaceHolder, int LineNum);

public:
	RLC_BytesDecoder(int lineNum, byte placeHolder);
	virtual ~RLC_BytesDecoder();

	ByteVecotrPtr transitData(ByteVecotrPtr src);
};

