#pragma once
#include "TransData.h"
#include "MyImage.h"

class RLC_GrayScaleEncoder :
	public TransData
{
private:
	typeImgPtr image;

public:
	RLC_GrayScaleEncoder(typeImgPtr img);
	RLC_GrayScaleEncoder(typeImgPtr img, TransData * pre);

	virtual ~RLC_GrayScaleEncoder();

	ByteVecotrPtr transitDataOwn(ByteVecotrPtr src);
};

