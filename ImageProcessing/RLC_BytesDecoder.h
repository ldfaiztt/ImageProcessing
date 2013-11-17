#pragma once
#include "TransData.h"
#include "MyImage.h"

class RLC_BytesDecoder :
	public TransData
{
private:
	byte PlaceHolder;
	int LineNum;

	ByteVecotrPtr DecoderWithoutTag(ByteVecotrPtr src);
	ByteVecotrPtr DecoderWithTag(ByteVecotrPtr src, byte PlaceHolder, int LineNum);

public:
	RLC_BytesDecoder(int lineNum, byte placeHolder);
	RLC_BytesDecoder(int lineNum, byte placeHOlder, TransData * preOP);

	virtual ~RLC_BytesDecoder();

	ByteVecotrPtr transitDataOwn(ByteVecotrPtr src);
};

