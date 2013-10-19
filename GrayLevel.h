#pragma once
#include "TransImage.h"
class GrayLevel :
	public TransImage
{
private:
	int srcL;
	int dstL;
	int GrayLevel::mapGrayL(int src);

public:
	GrayLevel();
	GrayLevel(typeImgParaPtr imgP);
	virtual ~GrayLevel();

	virtual typeImgPtr transit(typeImgPtr src);
};

