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
	NearestNeighbor(typeImgParaPtr imgP);
	virtual ~NearestNeighbor();

	virtual typeImgPtr transit(typeImgPtr src);
};

