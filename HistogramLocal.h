#pragma once
#include "HistogramEQ.h"
#include "ImageMask.h"

class HistogramLocal :
	public TransImage
{
private:
	int mask_size;
protected:
	shared_ptr<type_statistic_map> Statistic(shared_ptr<ImageMask> src);
public:
	HistogramLocal();
	HistogramLocal(shared_ptr<stImgPara> imgP);
	virtual ~HistogramLocal();

	virtual shared_ptr<CImage> transit(shared_ptr<CImage> src);
};

