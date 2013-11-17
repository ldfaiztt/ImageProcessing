#pragma once
#include "TransData.h"
#include "MyImage.h"

class RLC_BytesEncoder :
	public TransData
{
private:
	byte PlaceHolder;
	int LineNum;

	ByteVecotrPtr EncoderWithoutTag(ByteVecotrPtr src);
	ByteVecotrPtr EncoderWithTag(ByteVecotrPtr src, byte PlaceHolder, int LineNum);

protected:
	ByteVecotrPtr transitDataOwn(ByteVecotrPtr src);

public:
	RLC_BytesEncoder(int lineNum, byte placeHolder);
	RLC_BytesEncoder(int lineNum, byte placeHolder, TransData * pre);

	virtual ~RLC_BytesEncoder();
};

