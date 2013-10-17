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
	PowerScale(shared_ptr<stImgPara> imgP);
	virtual ~PowerScale();

	virtual shared_ptr<CImage> transit(shared_ptr<CImage> src);
};

