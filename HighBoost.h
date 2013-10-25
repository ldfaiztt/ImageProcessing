#pragma once
#include "TransImage.h"
class HighBoost :
	public TransImage
{
public:
	HighBoost();
	HighBoost(typeImgParaPtr imgP);
	virtual ~HighBoost();

	virtual typeImgPtr transit(typeImgPtr src);
};

