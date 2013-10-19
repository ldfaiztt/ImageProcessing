#pragma once
#include "TransImage.h"
class Graying :
	public TransImage
{
public:
	Graying();
	Graying(typeImgParaPtr imgP);
	virtual ~Graying();

	virtual typeImgPtr transit(typeImgPtr src);
};

