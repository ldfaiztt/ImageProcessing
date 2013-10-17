#pragma once
#include "TransImage.h"
class NearestNeighbor :
	public TransImage
{
private:
	int dstW;
	int dstH;

public:
	NearestNeighbor();
	NearestNeighbor(shared_ptr<stImgPara> imgP);
	virtual ~NearestNeighbor();

	virtual shared_ptr<CImage> transit(shared_ptr<CImage> src);
};

