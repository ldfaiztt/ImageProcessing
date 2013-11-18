#pragma once

#include "MyImage.h"

class RLC_BytesEncoder
{
private:
	byte PlaceHolder;
	int LineNum;

	ByteVecotrPtr EncoderWithoutTag(ByteVecotrPtr src);
	ByteVecotrPtr EncoderWithTag(ByteVecotrPtr src, byte PlaceHolder, int LineNum);

public:
	RLC_BytesEncoder(int lineNum, byte placeHolder);
	virtual ~RLC_BytesEncoder();

	ByteVecotrPtr transitData(ByteVecotrPtr src);
};

