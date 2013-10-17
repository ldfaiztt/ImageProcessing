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
	GrayLevel(shared_ptr<stImgPara> imgP);
	virtual ~GrayLevel();

	virtual shared_ptr<CImage> transit(shared_ptr<CImage> src);
};

