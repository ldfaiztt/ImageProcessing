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
	Subsampling(typeImgParaPtr imgP);
	virtual ~Subsampling();

	virtual typeImgPtr transit(typeImgPtr src);
};

