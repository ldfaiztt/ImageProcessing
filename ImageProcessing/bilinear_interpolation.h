#pragma once
#include "TransImage.h"
class BilinearInterpolation :
	public TransImage
{
private:
	int dstW;
	int dstH;

public:
	BilinearInterpolation();
	BilinearInterpolation(typeImgParaPtr imgP);
	virtual ~BilinearInterpolation();

	virtual typeImgPtr transit(typeImgPtr src);
};

