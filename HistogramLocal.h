#pragma once
#include "HistogramEQ.h"

class HistogramLocal :
	public HistogramEQ
{
private:
	int mask_size;

public:
	HistogramLocal();
	HistogramLocal(shared_ptr<stImgPara> imgP);
	virtual ~HistogramLocal();

	virtual shared_ptr<CImage> transit(shared_ptr<CImage> src);
};

