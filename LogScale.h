#pragma once
#include "TransImage.h"

class LogScale :
	public TransImage
{
private:
	float c;
	//float y;

	int Log(int inV);

public:
	LogScale();
	LogScale(shared_ptr<stImgPara> imgP);
	virtual ~LogScale();

	virtual shared_ptr<CImage> transit(shared_ptr<CImage> src);
};

