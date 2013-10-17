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
	BilinearInterpolation(shared_ptr<stImgPara> imgP);
	virtual ~BilinearInterpolation();

	virtual shared_ptr<CImage> transit(shared_ptr<CImage> src);
};

