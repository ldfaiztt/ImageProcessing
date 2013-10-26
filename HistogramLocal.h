#pragma once
#include "HistogramEQ.h"
#include "ImageMask.h"

class HistogramLocalFilter :
	public HistogramEQFilter
{
private:
	int mask_size;
public:
	HistogramLocalFilter();
	HistogramLocalFilter(shared_ptr<stImgPara> imgP);
	virtual ~HistogramLocalFilter();

	virtual typeImgPtr transit(typeImgPtr src);
};

