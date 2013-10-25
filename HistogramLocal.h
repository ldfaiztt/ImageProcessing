#pragma once
#include "HistogramEQ.h"
#include "ImageMask.h"

class HistogramLocal :
	public HistogramEQ
{
private:
	int mask_size;
public:
	HistogramLocal();
	HistogramLocal(shared_ptr<stImgPara> imgP);
	virtual ~HistogramLocal();

	virtual typeImgPtr transit(typeImgPtr src);
};

