#pragma once
#include "TransImage.h"
class Subsampling :
	public TransImage
{
private:
	int dstW;
	int dstH;

public:
	Subsampling();
	Subsampling(shared_ptr<stImgPara> imgP);
	virtual ~Subsampling();

	virtual shared_ptr<CImage> transit(shared_ptr<CImage> src);
};

