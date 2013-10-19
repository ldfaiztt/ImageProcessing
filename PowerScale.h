#pragma once
#include "TransImage.h"
class PowerScale :
	public TransImage
{
private:
	float c;
	float y;

	int Pow(int inV);

public:
	PowerScale();
	PowerScale(typeImgParaPtr imgP);
	virtual ~PowerScale();

	virtual typeImgPtr transit(typeImgPtr src);
};

