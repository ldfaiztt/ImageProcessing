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
	LogScale(typeImgParaPtr imgP);
	virtual ~LogScale();

	virtual typeImgPtr transit(typeImgPtr src);
};

