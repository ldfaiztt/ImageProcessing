#pragma once
#include "TransImage.h"

class LogScaleFilter :
	public TransImage
{
private:
	float c;
	//float y;

	int Log(int inV);

public:
	LogScaleFilter();
	LogScaleFilter(typeImgParaPtr imgP);
	virtual ~LogScaleFilter();

	virtual typeImgPtr transit(typeImgPtr src);
};

