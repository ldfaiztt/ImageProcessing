#pragma once
#include "TransData.h"
#include "MyImage.h"

class RLC_GrayScaleDecoder :
	public TransData
{
private:
	int NumPerLine;

public:
	RLC_GrayScaleDecoder(int Num);
	RLC_GrayScaleDecoder(int Num, TransData * preOP);

	virtual ~RLC_GrayScaleDecoder();

	ByteVecotrPtr transitDataOwn(ByteVecotrPtr src);
};

