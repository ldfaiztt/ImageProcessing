#pragma once
#include "TransImage.h"
class PowerScaleFilter :
	public TransImage
{
private:
	float c;
	float y;

	int Pow(int inV);

public:
	PowerScaleFilter();
	PowerScaleFilter(typeImgParaPtr imgP);
	virtual ~PowerScaleFilter();

	virtual typeImgPtr transit(typeImgPtr src);
};

