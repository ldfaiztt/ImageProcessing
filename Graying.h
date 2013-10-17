#pragma once
#include "TransImage.h"
class Graying :
	public TransImage
{
public:
	Graying();
	Graying(shared_ptr<stImgPara> imgP);
	virtual ~Graying();

	virtual shared_ptr<CImage> transit(shared_ptr<CImage> src);
};

