#pragma once
#include "TransImage.h"
class HistogramLocal :
	public TransImage
{
private:
	int mask_size;

public:
	HistogramLocal();
	HistogramLocal(shared_ptr<stImgPara> imgP);
	virtual ~HistogramLocal();

	virtual shared_ptr<CImage> transit(shared_ptr<CImage> src);
};

